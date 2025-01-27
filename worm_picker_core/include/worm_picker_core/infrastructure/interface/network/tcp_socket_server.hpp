// tcp_socket_server.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <netinet/in.h>
#include <rclcpp/rclcpp.hpp> 

class TcpSocketServer {
public:
    static constexpr size_t RECEIVE_BUFFER_SIZE = 2048;
    static constexpr int SOCKET_BACKLOG = 1;

    using CommandHandler = std::function<void(const std::string&, 
                                              std::function<void(bool, std::string)>)>;

    TcpSocketServer(uint16_t port);
    ~TcpSocketServer();
    bool startServer();
    void stopServer();
    void setCommandHandler(CommandHandler handler);

private:
    void initializeServerSocket();
    void waitForClientConnections();
    void handleClientConnection(int client_socket);
    void processReceivedData(std::string& buffer, int client_socket);
    void executeCommand(std::string_view command, int client_socket);

    const uint16_t port_;
    std::atomic<bool> is_running_{false};
    int server_socket_{-1};
    std::jthread server_thread_;
    CommandHandler command_handler_;
    std::mutex command_handler_mutex_;
};