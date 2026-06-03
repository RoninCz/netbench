#  NetBench-FromScratch

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-17%2B-orange.svg)](https://isocpp.org/)
[![Linux](https://img.shields.io/badge/platform-Linux-yellow.svg)](https://www.linux.org/)
[![Status](https://img.shields.io/badge/status-active-brightgreen.svg)]()

**从零实现的高性能 TCP/UDP/HTTP 网络压测与观测框架**

本项目旨在深入探索 Linux 传统网络协议栈的性能极限。不依赖 DPDK 或 XDP 等内核旁路技术，完全基于用户态 Socket 编程，通过精细化的系统调用优化，实现了一个类似 `wrk`、`iperf` 和 `tcpreplay` 的高性能网络压测工具。

项目核心聚焦于 **epoll** 与 **io_uring** 两种 I/O 多路复用机制的实战对比，以及在高并发场景下的延迟分布观测与性能调优。

---

##  核心特性

*   **多协议支持**：
    *   **TCP Echo**：标准的 TCP 回显压测，用于评估连接建立与数据往返性能。
    *   **UDP 收发**：支持指定包长的 UDP 流量发送与接收，统计丢包率。
    *   **HTTP/1.1**：轻量级 HTTP 客户端压测，支持 Keep-Alive 与 Pipeline。
*   **高性能 I/O 后端**：
    *   支持 **epoll** (ET/LT) 与 **io_uring** 两种后端无缝切换，直观对比新旧 I/O 机制的性能差异。
*   **极致性能优化**：
    *   **多线程模型**：基于 Reactor 模式的多线程架构。
    *   **CPU 亲和性 (Affinity)**：支持线程与 CPU 核心绑定，减少上下文切换与缓存失效。
    *   **零拷贝优化**：在应用层尽可能减少不必要的数据拷贝。
*   **深度可观测性**：
    *   **延迟分布统计**：精确计算 P50, P90, P99, P999 延迟，拒绝平均数陷阱。
    *   **全方位指标**：实时输出 QPS、吞吐量 (Throughput)、丢包数、TCP 重传及 CPU 使用率。
*   **安全扩展**：
    *   可选 **TLS** 模式，评估加密握手与数据传输对性能的损耗。

---

## ️ 技术栈与依赖

*   **编程语言**：C++17 / C++20
*   **构建系统**：CMake (>= 3.15)
*   **核心依赖**：
    *   Linux Kernel >= 5.10 (为了完整支持 `io_uring`)
    *   `liburing` (用于 io_uring 后端)
    *   `openssl` (用于 TLS 支持)
    *   `pthread`

---


