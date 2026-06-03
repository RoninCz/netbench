# 将 main.cpp 编译为可执行文件 netbench
add_executable(netbench main.cpp)

# 链接后续会开发的各个功能模块库
# 即使这些库现在还是空的，CMake 也能正常处理。
# 等后续你在各个子目录写好代码并定义了库，这里就能自动链接上。
target_link_libraries(netbench PRIVATE
    # common_lib
    # net_lib
    # backend_lib
    # server_lib
    # client_lib
)

# 如果后续引入了 OpenSSL 等第三方库，也在这里链接
# target_link_libraries(netbench PRIVATE OpenSSL::SSL OpenSSL::Crypto)
