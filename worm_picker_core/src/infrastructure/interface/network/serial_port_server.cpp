// serial_port_server.cpp
//
// Copyright (c) 2026
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/interface/network/serial_port_server.hpp"

#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/redirect_error.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/write.hpp>

using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
namespace this_coro = boost::asio::this_coro;

SerialPortServer::SerialPortServer(boost::asio::io_context& ctx,
                                   std::string device,
                                   unsigned baud_rate)
    : ctx_(ctx),
      port_(ctx_),
      device_(std::move(device)),
      baud_rate_(baud_rate),
      write_strand_(ctx_.get_executor())
{}

SerialPortServer::~SerialPortServer()
{
    stopServer();
}

bool SerialPortServer::openPort()
{
    boost::system::error_code ec;
    port_.open(device_, ec);
    if (ec) {
        RCLCPP_WARN(rclcpp::get_logger("serial_server"),
                    "open(%s): %s", device_.c_str(), ec.message().c_str());
        return false;
    }

    using sp = boost::asio::serial_port_base;
    port_.set_option(sp::baud_rate(baud_rate_),         ec);
    port_.set_option(sp::character_size(8),             ec);
    port_.set_option(sp::parity(sp::parity::none),      ec);
    port_.set_option(sp::stop_bits(sp::stop_bits::one), ec);
    port_.set_option(sp::flow_control(sp::flow_control::none), ec);

    if (ec) {
        RCLCPP_WARN(rclcpp::get_logger("serial_server"),
                    "set_option(%s): %s", device_.c_str(), ec.message().c_str());
        boost::system::error_code ignored;
        port_.close(ignored);
        return false;
    }

    RCLCPP_INFO(rclcpp::get_logger("serial_server"),
                "Opened %s at %u baud", device_.c_str(), baud_rate_);
    return true;
}

bool SerialPortServer::startServer()
{
    if (running_.exchange(true)) {
        return true;
    }

    try {
        co_spawn(ctx_, readLoop(), detached);
        return true;
    } catch (const std::exception& e) {
        RCLCPP_ERROR(rclcpp::get_logger("serial_server"),
                     "startServer: %s", e.what());
        running_ = false;
        return false;
    }
}

void SerialPortServer::stopServer()
{
    if (!running_.exchange(false)) {
        return;
    }

    boost::system::error_code ec;
    port_.cancel(ec);
    port_.close(ec);
}

void SerialPortServer::setCommandHandler(CommandHandler cb)
{
    std::scoped_lock lk(handler_mtx_);
    handler_ = std::move(cb);
}

awaitable<void> SerialPortServer::readLoop()
{
    auto exec = co_await this_coro::executor;
    boost::asio::streambuf buf(RECEIVE_BUFFER_SIZE);
    boost::asio::steady_timer retry_timer(exec);

    auto getHandler = [&]() -> std::optional<CommandHandler> {
        std::scoped_lock lk(handler_mtx_);
        if (handler_) return handler_;
        return std::nullopt;
    };

    while (running_) {
        if (!port_.is_open()) {
            if (!openPort()) {
                if (!running_) co_return;
                retry_timer.expires_after(std::chrono::seconds(2));
                boost::system::error_code tec;
                co_await retry_timer.async_wait(
                    boost::asio::redirect_error(boost::asio::use_awaitable, tec));
                continue;
            }
        }

        boost::system::error_code ec;
        std::size_t n = co_await boost::asio::async_read_until(
            port_, buf, '\n',
            boost::asio::redirect_error(boost::asio::use_awaitable, ec));

        if (!running_) co_return;

        if (ec) {
            RCLCPP_WARN(rclcpp::get_logger("serial_server"),
                        "read(%s): %s — re-opening", device_.c_str(), ec.message().c_str());
            boost::system::error_code ignored;
            port_.close(ignored);
            buf.consume(buf.size());
            continue;
        }

        if (n == 0) {
            continue;
        }

        if (buf.size() > MAX_LINE_LENGTH) {
            RCLCPP_WARN(rclcpp::get_logger("serial_server"),
                "Line too long (%zu bytes); flushing buffer", buf.size());
            buf.consume(buf.size());
            continue;
        }

        std::string line;
        {
            std::istream is(&buf);
            std::getline(is, line);
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
        }

        if (line.empty()) {
            continue;
        }

        if (auto maybe_h = getHandler()) {
            dispatchAndReply(std::move(*maybe_h), std::move(line));
        }
    }

    co_return;
}

void SerialPortServer::dispatchAndReply(CommandHandler h, std::string cmd)
{
    h(std::move(cmd), [this](Reply r) mutable {
        std::string out = r.isSuccess()
            ? "true\n"  + r.value() + '\n'
            : "false\n" + r.error() + '\n';

        auto payload = std::make_shared<std::string>(std::move(out));
        boost::asio::post(write_strand_, [this, payload]() {
            if (!running_ || !port_.is_open()) {
                return;
            }
            boost::asio::async_write(
                port_, boost::asio::buffer(*payload),
                [payload](auto /*ec*/, auto /*bytes*/) { /* keep payload alive */ });
        });
    });
}
