cmake_minimum_required(VERSION 3.16)

# 项目名，自行修改
project(wow VERSION 1.0)

# C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 生成command_compile.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 选择对应平台
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "OS: Windows")
    add_definitions(-DWIN32)  # 所有项目windows添加WIN32标识
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "OS: Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "OS: MacOS")
else()
    message(FATAL_ERROR "Unknow OS: ${CMAKE_SYSTEM_NAME}")
endif()

# 默认构建类型为Debug
set(CMAKE_BUILD_TYPE Debug)
# 默认启动网络构建，第三方库从网络下载构建
# 关闭后启动本地依赖，需要再本地指定路径手动下载预编译库
set(BUILD_FROM_NETWORK ON)
# 启动可视化图表构建
set(BUILD_IMPLOT ON)
# 编译Demo
set(BUILD_DEMO ON)

# 创建编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/dist/debug)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(STATUS "Using MSVC compiler")
        set(CMAKE_CXX_FLAGS "/utf-8 /Zi /Od /MDd /EHsc")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Using GCC compiler")
        set(CMAKE_CXX_FLAGS "-g -Wall -Wformat -Wl,-rpath,\$ORIGN/lib")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Using Clang compiler")
        set(CMAKE_CXX_FLAGS "-g -Wall -Wformat -Wl,-rpath,\$ORIGN/lib")
    else()
        message(FATAL_ERROR "Unknow Compile: ${CMAKE_CXX_COMPILER_ID}")
    endif()
else()
    set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/dist/release)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(STATUS "Using MSVC compiler")
        set(CMAKE_CXX_FLAGS "/utf-8 /O2 /MD /DNDEBUG /EHsc")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Using GCC compiler")
        set(CMAKE_CXX_FLAGS "-O2 -DNDEBUG -Wl,-rpath,\$ORIGN/lib")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Using Clang compiler")
        set(CMAKE_CXX_FLAGS "-O2 -DNDEBUG -Wl,-rpath,\$ORIGN/lib")
    else()
        message(FATAL_ERROR "Unknow Compile: ${CMAKE_CXX_COMPILER_ID}")
    endif()
endif()

if(BUILD_FROM_NETWORK)
    include(FetchContent)
else()
    set(SPDLOG_DIR ${PROJECT_SOURCE_DIR}/spdlog)
    set(GLFW_DIR ${PROJECT_SOURCE_DIR}/glfw)
    set(JSON_DIR ${PROJECT_SOURCE_DIR}/nlohmann-json)
endif()

add_subdirectory(imgui)
add_subdirectory(common)
add_subdirectory(app)
add_subdirectory(demo)

# cmake配置
# install(FILES ${PROJECT_SOURCE_DIR}/cmake/wowConfig.cmake DESTINATION .)
