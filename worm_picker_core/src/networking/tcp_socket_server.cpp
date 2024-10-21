// tcp_socket_server.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
//
// Licensed under the Apache License, Version 2.0 (the "License");

#include "worm_picker_core/networking/tcp_socket_server.hpp"

TcpSocketServer::TcpSocketServer(int server_port)
    : server_socket_file_descriptor_(-1), server_port_(server_port), is_server_running_(false)
{
}

TcpSocketServer::~TcpSocketServer()
{
    stopServer();
}

void TcpSocketServer::startServer()
{
    if (is_server_running_) {
        return;
    }

    try {
        initializeServerSocket();
        is_server_running_ = true;
        server_thread_ = std::thread(&TcpSocketServer::waitForClientConnections, this);
    } catch (const std::exception& exception) {
        cleanupServerSocket();
        throw;
    }
}

void TcpSocketServer::stopServer()
{
    if (!is_server_running_) {
        return;
    }

    cleanupServerSocket();

    if (server_thread_.joinable()) {
        server_thread_.join();
    }
}

void TcpSocketServer::initializeServerSocket()
{
    server_socket_file_descriptor_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_file_descriptor_ == -1) {
        throw std::runtime_error("Failed to create server socket: " + std::string(std::strerror(errno)));
    }

    int enable_address_reuse_option = 1;
    if (setsockopt(server_socket_file_descriptor_, SOL_SOCKET, SO_REUSEADDR, &enable_address_reuse_option, sizeof(enable_address_reuse_option)) == -1) {
        throw std::runtime_error("Failed to set socket options: " + std::string(std::strerror(errno)));
    }

    sockaddr_in server_socket_address;
    std::memset(&server_socket_address, 0, sizeof(server_socket_address));
    server_socket_address.sin_family = AF_INET;
    server_socket_address.sin_addr.s_addr = INADDR_ANY;
    server_socket_address.sin_port = htons(server_port_);

    if (bind(server_socket_file_descriptor_, reinterpret_cast<sockaddr*>(&server_socket_address), sizeof(server_socket_address)) == -1) {
        throw std::runtime_error("Failed to bind server socket: " + std::string(std::strerror(errno)));
    }

    if (listen(server_socket_file_descriptor_, SOCKET_BACKLOG) == -1) {
        throw std::runtime_error("Failed to listen on server socket: " + std::string(std::strerror(errno)));
    }
}

void TcpSocketServer::waitForClientConnections() 
{
    while (is_server_running_) {
        sockaddr_in client_socket_address{};
        socklen_t client_socket_address_len = sizeof(client_socket_address);

        int client_socket_file_descriptor = accept(server_socket_file_descriptor_, reinterpret_cast<sockaddr*>(&client_socket_address), &client_socket_address_len);

        if (client_socket_file_descriptor == -1) {
            if (is_server_running_) {
                if (errno == EINTR) continue;
                if (errno == EBADF || errno == EINVAL) break;
                continue;
            } else {
                break; 
            }
        } else {
            std::thread(&TcpSocketServer::handleClientConnection, this, client_socket_file_descriptor).detach();
        }
    }
}

void TcpSocketServer::handleClientConnection(int client_socket_file_descriptor) 
{
    char receive_buffer[RECEIVE_BUFFER_SIZE];
    std::string complete_received_data;

    while (is_server_running_) {
        ssize_t bytes_received = recv(client_socket_file_descriptor, receive_buffer, sizeof(receive_buffer), 0);

        if (bytes_received > 0) {
            complete_received_data.append(receive_buffer, bytes_received);
            processReceivedData(complete_received_data, client_socket_file_descriptor);
        } else if (bytes_received == 0) {
            break;
        } else {
            if (errno == EINTR) {
                continue; 
            }
            break; 
        }
    }
    close(client_socket_file_descriptor);
}

void TcpSocketServer::processReceivedData(std::string& received_data_buffer, int client_socket_file_descriptor) 
{
    size_t newline_position_index;
    while ((newline_position_index = received_data_buffer.find('\n')) != std::string::npos) {
        std::string extracted_command = received_data_buffer.substr(0, newline_position_index);
        
        if (!extracted_command.empty() && extracted_command.back() == '\r') {
            extracted_command.pop_back();
        }

        executeCommand(extracted_command, client_socket_file_descriptor);
        received_data_buffer.erase(0, newline_position_index + 1);
    }
}

void TcpSocketServer::executeCommand(const std::string& received_command, int client_socket_file_descriptor) 
{
    CommandHandler active_command_handler;
    {
        std::lock_guard<std::mutex> lock(command_handler_mutex_);
        active_command_handler = command_handler_;
    }

    if (active_command_handler) {
        active_command_handler(received_command, [this, client_socket_file_descriptor](bool success) {
            const std::string response = success ? "true\n" : "false\n";
            send(client_socket_file_descriptor, response.c_str(), response.size(), 0);
        });
    }
}

void TcpSocketServer::setCommandHandler(CommandHandler new_command_handler) 
{
    std::lock_guard<std::mutex> lock(command_handler_mutex_);
    command_handler_ = new_command_handler;
}

void TcpSocketServer::cleanupServerSocket() 
{
    if (server_socket_file_descriptor_ != -1) {
        shutdown(server_socket_file_descriptor_, SHUT_RDWR);
        close(server_socket_file_descriptor_);
        server_socket_file_descriptor_ = -1;
    }
}