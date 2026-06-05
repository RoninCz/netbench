#pragma once
#include "socket.hpp"
#include <string>

namespace netbench {

class TcpConnection {
public:
    explicit TcpConnection(SocketFd socket) : socket_(std::move(socket)) {}

    ssize_t send(const void* buf, size_t len);

    ssize_t recv(void* buf, size_t len);

    int fd() const { return socket_.get();}

private:
    SocketFd socket_;
};
} //namespace netbench