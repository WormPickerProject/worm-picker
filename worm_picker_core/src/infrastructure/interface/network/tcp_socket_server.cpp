// tcp_socket_server.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/interface/network/tcp_socket_server.hpp"

#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/redirect_error.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/write.hpp>

using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::ip::tcp;
namespace this_coro = boost::asio::this_coro;

TcpSocketServer::TcpSocketServer(boost::asio::io_context& ctx, uint16_t port)
    : ctx_(ctx),
      acceptor_(ctx_, tcp::endpoint(tcp::v4(), port))
{}

TcpSocketServer::~TcpSocketServer() 
{ 
    stopServer(); 
}

bool TcpSocketServer::startServer()
{
    if (running_.exchange(true)) {
        return true;
    }

    try {
        co_spawn(ctx_, acceptLoop(), detached);
        return true;
    } catch (const std::exception& e) {
        RCLCPP_ERROR(rclcpp::get_logger("tcp_server"), "startServer: %s", e.what());
        running_ = false;
        return false;
    }
}

void TcpSocketServer::stopServer()
{
    if (!running_.exchange(false)) {
        return;
    }

    boost::system::error_code ec;
    acceptor_.close(ec);

    std::lock_guard lk(sessions_mtx_);
    for (auto it = sessions_.begin(); it != sessions_.end(); ) {
        if (auto s = it->lock()) {
            s->cancel(ec);
            s->close(ec);
            ++it;
        } else {
            it = sessions_.erase(it);
        }
    }
}

void TcpSocketServer::setCommandHandler(CommandHandler cb)
{
    std::scoped_lock lk(handler_mtx_);
    handler_ = std::move(cb);
}

awaitable<void> TcpSocketServer::acceptLoop()
{
    auto exec = co_await this_coro::executor;

    while (running_) {
        boost::system::error_code ec;
        tcp::socket sock = co_await acceptor_.async_accept(
            boost::asio::redirect_error(boost::asio::use_awaitable, ec));

        if (!running_) {
            co_return;
        }
        if (ec) {
            RCLCPP_WARN(rclcpp::get_logger("tcp_server"), "accept(): %s", ec.message().c_str());
            continue;
        }

        auto sock_ptr = std::make_shared<tcp::socket>(std::move(sock));

        {
            std::lock_guard lk(sessions_mtx_);
            sessions_.emplace_back(sock_ptr);
        }

        co_spawn(exec, session(sock_ptr), detached);
    }
}

awaitable<void> TcpSocketServer::session(SocketPtr sock)
{
    boost::asio::streambuf buf(RECEIVE_BUFFER_SIZE);

    auto getHandler = [&]() -> std::optional<CommandHandler> {
        std::scoped_lock lk(handler_mtx_);
        if (handler_) return handler_;
        return std::nullopt;
    };

    while (running_) {
        std::size_t n = 0;
        try {
            n = co_await boost::asio::async_read_until(
                *sock, buf, '\n', boost::asio::use_awaitable);
        } catch (const std::exception& e) {
            RCLCPP_INFO(rclcpp::get_logger("tcp_server"), "session closed: %s", e.what());
            co_return;
        }

        if (n == 0) {
            co_return;
        }

        if (buf.size() > MAX_LINE_LENGTH) {
            RCLCPP_WARN(rclcpp::get_logger("tcp_server"),
                "Line too long (%zu bytes); disconnecting", buf.size());
            boost::system::error_code ec;
            sock->close(ec);
            co_return;
        }

        std::string line;
        {
            std::istream is(&buf);
            std::getline(is, line);
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
        }

        if (auto maybe_h = getHandler()) {
            dispatchAndReply(sock, std::move(*maybe_h), std::move(line));
        }
    }

    {
        std::lock_guard lk(sessions_mtx_);
        std::erase_if(sessions_,
                      [sock](const std::weak_ptr<tcp::socket>& w)
                      { return w.expired() || w.lock() == sock; });
    }
    
    co_return;
}

void TcpSocketServer::dispatchAndReply(SocketPtr sock, CommandHandler h, std::string cmd)
{
    auto exec = sock->get_executor();
    h(std::move(cmd), [sock](Reply r) mutable {
        std::string out = r.isSuccess()
            ? "true\n"  + r.value() + '\n'
            : "false\n" + r.error() + '\n';

        auto payload = std::make_shared<std::string>(std::move(out));
        boost::asio::async_write(
            *sock, boost::asio::buffer(*payload),
            [sock, payload](auto /*ec*/, auto /*bytes*/) { /* keep socket & payload alive */ });
    });
}