# 将当前目录下的所有 .cpp 文件收集起来，编译成名为 net_lib 的静态库
#add_library(net_lib STATIC
    # 后续在这里添加具体的源文件
#)

# 设置该库的头文件包含目录
# PUBLIC 表示：不仅编译 common_lib 自己时需要这些头文件，
# 链接了 common_lib 的其他目标（比如最终的 netbench 可执行文件）也能自动获得这些头文件路径
#target_include_directories(net_lib PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}
#)

# 第三方库依赖（比如 pthread），在这里链接
# target_link_libraries(net_lib PUBLIC pthread)
