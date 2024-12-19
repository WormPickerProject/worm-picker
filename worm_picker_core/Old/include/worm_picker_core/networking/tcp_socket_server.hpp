// tcp_socket_server.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef TCP_SOCKET_SERVER_HPP
#define TCP_SOCKET_SERVER_HPP

#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <functional>
#include <atomic>
#include <mutex>
#include <stdexcept>
#include <cerrno>
#include <system_error>
#include <thread>
#include <cstring>

#include <rclcpp/rclcpp.hpp> 

constexpr int RECEIVE_BUFFER_SIZE = 1024;  // Buffer size for receiving data
constexpr int SOCKET_BACKLOG = 1;  // Backlog for socket listen calls

/** 
 * @brief TCP Socket Server class that handles incoming client connections, receives commands,
 *        and processes them using a provided command handler function.
 */
class TcpSocketServer
{
public:
    /** 
     * @brief Type definition for the command handler function.
     *        It takes a received command string and a callback function to return the result.
     */
    using CommandHandler = std::function<void(const std::string&, std::function<void(bool)>)>;

    /**
     * @brief Constructs a TcpSocketServer object that listens on the specified port.
     * @param server_port Port number on which the server will listen for incoming connections.
     */
    TcpSocketServer(int server_port);

    /** 
     * @brief Destructor that cleans up the server resources.
     */
    ~TcpSocketServer();

    /** 
     * @brief Starts the TCP socket server and begins listening for incoming client connections.
     *        This method will block the calling thread.
     */
    void startServer();

    /** 
     * @brief Stops the TCP socket server and closes any open client connections.
     */
    void stopServer();

    /** 
     * @brief Sets the command handler function that will be called when a command is received
     *        from a connected client.
     * @param new_command_handler The command handler function to be used for processing commands.
     */
    void setCommandHandler(CommandHandler new_command_handler);

private:
    /** 
     * @brief Initializes the server socket and binds it to the specified port.
     * @throws std::runtime_error if socket creation, setting options, binding, or listening fails.
     */
    void initializeServerSocket();

    /** 
     * @brief Waits for incoming client connections and handles them in a blocking manner.
     */
    void waitForClientConnections();

    /** 
     * @brief Handles communication with a connected client.
     * @param client_socket_file_descriptor File descriptor for the connected client's socket.
     */
    void handleClientConnection(int client_socket_file_descriptor);

    /** 
     * @brief Processes the data received from the client and extracts individual commands.
     * @param received_data_buffer The buffer containing the data received from the client.
     * @param client_socket_file_descriptor File descriptor for the connected client's socket.
     */
    void processReceivedData(std::string& received_data_buffer, int client_socket_file_descriptor);

    /** 
     * @brief Executes the received command using the registered command handler.
     * @param received_command The command received from the client as a string.
     * @param client_socket_file_descriptor File descriptor for the connected client's socket.
     */
    void executeCommand(const std::string& received_command, int client_socket_file_descriptor);

    /** 
     * @brief Cleans up and closes the server socket.
     */
    void cleanupServerSocket();

    std::thread server_thread_;  // Thread for running the socket server
    int server_socket_file_descriptor_;  // File descriptor for the server's socket. 
    int server_port_;  // Port number on which the server listens.
    std::atomic<bool> is_server_running_;  // Atomic flag indicating if the server is running.

    CommandHandler command_handler_;  // The handler function for processing received commands.
    std::mutex command_handler_mutex_;  // Mutex for synchronizing access to the command handler.
};

#endif // TCP_SOCKET_SERVER_HPP