// tcp_socket_server.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/interface/network/tcp_socket_server.hpp"

TcpSocketServer::TcpSocketServer(uint16_t port)
    : port_(port)
{}

TcpSocketServer::~TcpSocketServer()
{
    stopServer();
}

bool TcpSocketServer::startServer()
{
    if (is_running_) {
        return true;
    }

    try {
        initializeServerSocket();
        is_running_ = true;
        server_thread_ = std::jthread([this]() {
            waitForClientConnections();
        });
        return true;
    } catch (const std::exception& e) {
        RCLCPP_ERROR(rclcpp::get_logger("tcp_server"), "Failed to start server: %s", e.what());
        if (server_socket_ != -1) {
            close(server_socket_);
            server_socket_ = -1;
        }
        return false;
    }
}

void TcpSocketServer::stopServer()
{
    if (!is_running_) {
        return;
    }

    is_running_ = false;
    
    if (server_socket_ != -1) {
        shutdown(server_socket_, SHUT_RDWR);
        close(server_socket_);
        server_socket_ = -1;
    }
}

void TcpSocketServer::initializeServerSocket()
{
    server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_ == -1) {
        throw std::runtime_error("Failed to create socket: " + std::string(strerror(errno)));
    }

    int enable = 1;
    if (setsockopt(server_socket_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1) {
        throw std::runtime_error("Failed to set socket options: " + std::string(strerror(errno)));
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port_);

    if (bind(server_socket_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
        throw std::runtime_error("Failed to bind socket: " + std::string(strerror(errno)));
    }

    if (listen(server_socket_, SOCKET_BACKLOG) == -1) {
        throw std::runtime_error("Failed to listen on socket: " + std::string(strerror(errno)));
    }
}

void TcpSocketServer::waitForClientConnections()
{
    while (is_running_) {
        sockaddr_in client_addr{};
        socklen_t addr_len = sizeof(client_addr);

        int client_socket = accept(
            server_socket_,
            reinterpret_cast<sockaddr*>(&client_addr),
            &addr_len
        );

        if (client_socket == -1) {
            if (!is_running_) break;
            if (errno == EINTR) continue;
            if (errno == EBADF || errno == EINVAL) break;
            continue;
        }

        std::jthread([this, client_socket]() {
            handleClientConnection(client_socket);
        }).detach();
    }
}

void TcpSocketServer::handleClientConnection(int client_socket) 
{
    std::array<char, RECEIVE_BUFFER_SIZE> buffer;
    std::string received_data;

    while (is_running_) {
        ssize_t bytes = recv(client_socket, buffer.data(), buffer.size(), 0);

        if (bytes > 0) {
            received_data.append(buffer.data(), bytes);
            processReceivedData(received_data, client_socket);
        } else if (bytes == 0) {
            break;
        } else {
            if (errno == EINTR) {
                continue; 
            }
            break; 
        }
    }

    close(client_socket);
}

void TcpSocketServer::processReceivedData(std::string& buffer, int client_socket) 
{
    size_t pos;
    while ((pos = buffer.find('\n')) != std::string::npos) {
        std::string_view command(buffer.data(), pos);
        if (!command.empty() && command.back() == '\r') {
            command.remove_suffix(1);
        }

        executeCommand(command, client_socket);
        buffer.erase(0, pos + 1);
    }
}

void TcpSocketServer::executeCommand(std::string_view command, int client_socket) 
{
    CommandHandler handler;
    {
        std::lock_guard<std::mutex> lock(command_handler_mutex_);
        handler = command_handler_;
    }

    if (handler) {
        handler(std::string(command), [client_socket](bool success, std::string feedback) {
            std::string response = 
                std::string(success ? "true\n" : "false\n") +
                std::string(feedback) + "\n";
                
            send(client_socket, response.data(), response.size(), 0);
        });
    }
}

void TcpSocketServer::setCommandHandler(CommandHandler handler) 
{
    std::lock_guard<std::mutex> lock(command_handler_mutex_);
    command_handler_ = std::move(handler);
}