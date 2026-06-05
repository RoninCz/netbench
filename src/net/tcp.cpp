#include "tcp.hpp"
#include <sys/socket.h>
#include <stdexcept>

namespace netbench {

ssize_t TcpConnection::send(const void* buf, size_t len) {
    ssize_t n = ::send(socket_.get(), buf, len, 0);
    if (n < 0) throw std::runtime_error("[ERROR] TCP Send failed");
    return n;
}

ssize_t TcpConnection::recv(void* buf, size_t len) {
    ssize_t n = ::recv(socket_.get(), buf, len, 0);
    if (n < 0) throw std::runtime_error("[ERROR] TCP Receive failed");
    return n;
}

} //namespace netbench