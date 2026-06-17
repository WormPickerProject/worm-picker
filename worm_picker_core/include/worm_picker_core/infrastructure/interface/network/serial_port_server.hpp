// serial_port_server.hpp
//
// Copyright (c) 2026
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <boost/asio.hpp>
#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/core/result.hpp"

class SerialPortServer {
public:
    static constexpr std::size_t RECEIVE_BUFFER_SIZE = 2048;
    static constexpr std::size_t MAX_LINE_LENGTH     = 8192;

    using Reply          = Result<std::string>;
    using ReplyFn        = std::function<void(Reply)>;
    using CommandHandler = std::function<void(const std::string&, ReplyFn)>;

    SerialPortServer(boost::asio::io_context& ctx,
                     std::string device,
                     unsigned baud_rate);
    ~SerialPortServer();
    bool startServer();
    void stopServer();
    void setCommandHandler(CommandHandler cb);

private:
    using IoExecutor = boost::asio::io_context::executor_type;
    using IoStrand   = boost::asio::strand<IoExecutor>;

    bool openPort();
    boost::asio::awaitable<void> readLoop();
    void dispatchAndReply(CommandHandler h, std::string cmd);

    boost::asio::io_context&        ctx_;
    boost::asio::serial_port        port_;
    std::string                     device_;
    unsigned                        baud_rate_;
    std::atomic<bool>               running_{false};
    std::mutex                      handler_mtx_;
    CommandHandler                  handler_;
    IoStrand                        write_strand_;
};
