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
        co_spawn(exec, session(std::move(sock)), detached);
    }
}

awaitable<void> TcpSocketServer::session(tcp::socket sock)
{
    boost::asio::streambuf buf(RECEIVE_BUFFER_SIZE);

    try {
        while (running_) {
            std::size_t n = co_await boost::asio::async_read_until(
                sock, buf, '\n', boost::asio::use_awaitable);
            if (n == 0) {
                break;
            }

            std::istream is(&buf);
            std::string line;
            std::getline(is, line);
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }

            CommandHandler h;
            { std::scoped_lock lk(handler_mtx_); h = handler_; }
            if (!h) {
                continue;
            }

            auto exec = sock.get_executor();
            h(line, [this,&sock,exec](Reply r) {
                boost::asio::post(exec, [this,&sock,r]() mutable { enqueueResponse(sock, r); });
            });
        }
    } catch (const std::exception& e) {
        RCLCPP_INFO(rclcpp::get_logger("tcp_server"), "session closed: %s", e.what());
    }
    co_return;
}

void TcpSocketServer::enqueueResponse(tcp::socket& sock, const Reply& r)
{
    std::string data = r.isSuccess()
        ? "true\n"  + r.value() + '\n'
        : "false\n" + r.error() + '\n';

    auto payload = std::make_shared<std::string>(std::move(data));

    boost::asio::async_write(
        sock, boost::asio::buffer(*payload),
        [payload](auto, auto) { /* keep shared_ptr alive */ });
}