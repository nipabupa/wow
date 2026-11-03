cmake_minimum_required(VERSION 3.16)

# 项目名，自行修改
project(wow VERSION 1.0)

# C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 生成command_compile.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 默认启动网络构建，第三方库从网络下载构建
# 关闭后启动本地依赖，需要再本地指定路径手动下载预编译库
option(ENABLE_NETWORK "download deps from network" ON)
# 启动可视化图表构建
option(ENABLE_IMPLOT "enable implot" ON)
# 启动Demo构建
option(ENABLE_DEMO "enable demo" ON)

# 创建编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_library(wow_flags INTERFACE)
    target_compile_options(wow_flags INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8 /Zi /Od /MDd /EHsc>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g -Wall -Wformat -Wl,-rpath,\$ORIGN/lib>
    )
else()
    add_library(wow_flags INTERFACE)
    target_compile_options(wow_flags INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8 /O2 /MD /DNDEBUG /EHsc>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O2 -DNDEBUG -Wl,-rpath,\$ORIGN/lib>
    )
endif()

if(ENABLE_NETWORK)
    include(FetchContent)
else()
    option(SPDLOG_DIR "spdlog dir" ${PROJECT_SOURCE_DIR}/spdlog)
    option(GLFW_DIR "glfw dir" ${PROJECT_SOURCE_DIR}/glfw)
    option(JSON_DIR "json dir" ${PROJECT_SOURCE_DIR}/nlohmann-json)
endif()

add_subdirectory(imgui)
add_subdirectory(common)
add_subdirectory(app)
if(ENABLE_DEMO)
    add_subdirectory(demo)
endif()
