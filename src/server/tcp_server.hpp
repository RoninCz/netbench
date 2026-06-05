#pragma once
#include <cstdint>
#include <string>

namespace netbench {

class TcpServer {
public:
    explicit TcpServer(uint16_t port) : port_(port) {}

    void run_block();

private:
    uint16_t port_;
};

} //namespace netbench