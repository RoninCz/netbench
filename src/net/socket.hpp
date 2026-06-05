#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdint>
#include <string>
#include <stdexcept>

namespace netbench {

class SocketFd {
public:
    explicit SocketFd(int fd = -1) : fd_(fd) {}
    ~SocketFd();

    SocketFd(const SocketFd&) = delete;
    SocketFd& operator=(const SocketFd&) = delete;

    SocketFd(SocketFd&& other) noexcept;
    SocketFd& operator=(SocketFd&& other) noexcept;

    int get() const { return fd_; }
    bool is_valid() const { return fd_ >= 0; }

private:
    int fd_;
};

class Socket {
public:
    static SocketFd create_tcp_socket();

    static void bind(const SocketFd& socket, std::uint16_t port);

    static void listen(const SocketFd& socket, int backlog = 1024);

    static SocketFd accept(const SocketFd& socket, sockaddr_in& client_addr);

    static void connect(const SocketFd& socket, const std::string& ip, std::uint16_t port);
};

} // namespace netbench