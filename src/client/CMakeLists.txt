# 将当前目录下的所有 .cpp、.hpp 文件收集起来，编译成静态库
#add_library(client_lib STATIC
    # 后续在这里添加具体的源文件
#)

# 设置该库的头文件包含目录
# PUBLIC 表示：不仅编译 client_lib 自己时需要这些头文件，
# 链接了 client_lib 的其他目标（比如最终的 netbench 可执行文件）也能自动获得这些头文件路径
#target_include_directories(client_lib PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}
#)

# 第三方库依赖（比如 pthread），在这里链接
# target_link_libraries(client_lib PUBLIC pthread)

