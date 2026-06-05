#pragma once
#include <cstdint>
#include <string>

namespace netbench {

class TcpClient {
public:
    TcpClient(const std::string& target_ip, uint16_t target_port, size_t payload_size)
        : target_ip_(target_ip), target_port_(target_port), payload_size_(payload_size) {}
    
    // 执行一次压测请求
    bool run_once();

private:
    std::string target_ip_;
    uint16_t target_port_;
    size_t payload_size_;
};

} // namespace netbench