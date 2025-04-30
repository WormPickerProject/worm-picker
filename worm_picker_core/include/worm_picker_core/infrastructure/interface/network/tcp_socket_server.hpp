// tcp_socket_server.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <boost/asio.hpp>
#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/core/result.hpp"

class TcpSocketServer {
public:
    static constexpr std::size_t RECEIVE_BUFFER_SIZE = 2048;
    static constexpr std::size_t MAX_LINE_LENGTH     = 8192;

    using Reply          = Result<std::string>;
    using ReplyFn        = std::function<void(Reply)>;
    using CommandHandler = std::function<void(const std::string&, ReplyFn)>;

    TcpSocketServer(boost::asio::io_context& ctx, uint16_t port);
    ~TcpSocketServer();
    bool startServer();
    void stopServer();
    void setCommandHandler(CommandHandler cb);

private:
    using SocketPtr      = std::shared_ptr<boost::asio::ip::tcp::socket>;
    using SocketWeakPtr = std::weak_ptr<boost::asio::ip::tcp::socket>;

    boost::asio::awaitable<void> acceptLoop();
    boost::asio::awaitable<void> session(SocketPtr sock);
    void dispatchAndReply(SocketPtr sock, CommandHandler h, std::string cmd);

    boost::asio::io_context&                 ctx_;
    boost::asio::ip::tcp::acceptor           acceptor_;
    std::atomic<bool>                        running_{false};
    std::mutex                               handler_mtx_;
    CommandHandler                           handler_;
    std::mutex                               sessions_mtx_;
    std::vector<SocketWeakPtr>               sessions_;
};