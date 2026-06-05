#include "tcp_client.hpp"
#include "socket.hpp"
#include "tcp.hpp"
#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>

namespace netbench {

bool TcpClient::run_once() {
    // 创建TCP套接字
    SocketFd socket = Socket::create_tcp_socket();
    Socket::connect(socket, target_ip_, target_port_);
    TcpConnection connection(std::move(socket));

    // 构造固定长度的payload
    std::vector<char> payload(payload_size_, 'A');

    // 发送数据
    ssize_t bytes_sent = connection.send(payload.data(), payload.size());
    if(bytes_sent != static_cast<ssize_t>(payload.size())) {
        std::cerr << "[ERROR] TCP send incomplete" << std::endl;
        return false;
    }

    // 接收并返回长度
    std::vector<char> buffer(payload_size_);
    size_t total_recv = 0;
    while(total_recv < payload_size_) {
        ssize_t bytes_recv = connection.recv(buffer.data() + total_recv, buffer.size() - total_recv);
        if(bytes_recv <= 0) {
            std::cerr << "[ERROR] TCP receive error or connection closed" << std::endl;
            return false;
        }
        total_recv += bytes_recv;
    }

    if(total_recv != payload_size_) {
        std::cerr << "[ERROR] Length mismatch: excepted " << payload_size_
                  << ", got " << total_recv << std::endl;
        return false;
    }

    return true;
}

}