#include "socket.hpp"
#include <unistd.h>
#include <cstring>
#include <format>
#include <arpa/inet.h>

namespace netbench {

SocketFd::~SocketFd() {
    if (is_valid()) ::close(fd_);
}

SocketFd::SocketFd(SocketFd&& other) noexcept : fd_(other.fd_) {
    other.fd_ = -1;
}

SocketFd& SocketFd::operator=(SocketFd&& other) noexcept {
    if(this != &other) {
        if(is_valid()) ::close(fd_);
        fd_ = other.fd_;
        other.fd_ = -1;
    }
    return *this;
}

SocketFd Socket::create_tcp_socket() {
    int fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd < 0) throw std::runtime_error("[ERROR] Failed to create TCP socket");
    return SocketFd(fd);
}

void Socket::bind(const SocketFd& socket, std::uint16_t port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if(::bind(socket.get(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        throw std::runtime_error("[ERROR] Failed to bind socket to port " + std::to_string(port) + ": " + std::strerror(errno));
    }
}

void Socket::listen(const SocketFd& socket, int backlog) {
    if(::listen(socket.get(), backlog) < 0) {
        throw std::runtime_error(std::format("[ERROR] Failed to listen on socket: ", std::strerror(errno)));
    }
}

SocketFd Socket::accept(const SocketFd& socket, sockaddr_in& client_addr) {
    socklen_t addr_len = sizeof(client_addr);
    int client_fd = ::accept(socket.get(), reinterpret_cast<sockaddr*>(&client_addr), &addr_len);
    if (client_fd < 0) {
        throw std::runtime_error(std::format("[ERROR] Failed to accept connection: ", std::strerror(errno)));
    }
    return SocketFd(client_fd);
}

void Socket::connect(const SocketFd& socket, const std::string& ip, std::uint16_t port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if(::inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0) {
        throw std::runtime_error("[ERROR] Invalid IP address: " + ip);
    }

    if(::connect(socket.get(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        throw std::runtime_error(std::format("[ERROR] Failed to connect to {}:{}", ip, port) + std::strerror(errno));
    }
}

}