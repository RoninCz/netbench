cmake_minimum_required(VERSION 3.15)
project(NetBenchLab LANGUAGES CXX)

# --- 全局基础设置 ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 生成 compile_commands.json，方便 VSCode/Clangd 代码补全

# 设置默认构建类型为 Release（如果用户没有指定）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# --- 查找第三方依赖 (预留) ---
# 例如后续你需要用到 OpenSSL 或 liburing，可以在这里统一查找
# find_package(OpenSSL REQUIRED)
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(LIBURING REQUIRED liburing)

# --- 引入子目录 ---
# 按照依赖顺序或逻辑顺序引入。
# 注意：这里假设 common 是最基础的，其他模块可能会依赖它
add_subdirectory(src/common)
add_subdirectory(src/net)
add_subdirectory(src/backend)
add_subdirectory(src/server)
add_subdirectory(src/client)
# add_subdirectory(src/report)

# 最后编译主程序（因为主程序依赖上面所有的库）
add_subdirectory(src)
