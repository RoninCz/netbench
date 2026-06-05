#include "tcp_server.hpp"
#include "socket.hpp"
#include "tcp.hpp"
#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>

namespace netbench {

void TcpServer::run_block() {
    // 创建tcp socket并绑定端口
    SocketFd listen_socket = Socket::create_tcp_socket();
    Socket::bind(listen_socket, port_);
    // 开始监听
    Socket::listen(listen_socket);

    std::cout << "[INFO]TCP server is listening on port " << port_ << std::endl;

    // 接受连接并处理（echo服务）
    while(true) {
        sockaddr_in client_addr{};
        SocketFd client_socket = Socket::accept(listen_socket, client_addr);
        TcpConnection connection(std::move(client_socket));

        std::cout << "[INFO]Accepted connection from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;

        // echo 循环
        std::vector<char> buffer(1024);
        while(true) {
            ssize_t n = connection.recv(buffer.data(), buffer.size());
            if(n == 0) {
                std::cerr << "[WARN]Client connect failed" << std::endl;
                break;
            } // 客户端断开连接

            // 原样返回
            ssize_t sent = connection.send(buffer.data(), n);
            if(sent < n) {
                std::cerr << "[WARN]Failed to send all data back to client" << std::endl;
                break;
            }
        }
    }
}

}