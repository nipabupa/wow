cmake_minimum_required(VERSION 4.0)

project(wow VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 生成compile_command.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_IMPLOT OFF)

file(GLOB_RECURSE WOW_UI_SOURCES src/wow_ui/*.cpp)
file(GLOB_RECURSE WOW_SUBPROCESS_SOURCES src/wow_subprocess/*.cpp)
file(GLOB_RECURSE WOW_SOCKET_SOURCES src/wow_socket/*.cpp)
file(GLOB_RECURSE WOW_SERIAL_SOURCES src/wow_serial/*.cpp)

# 选择对应平台
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "OS: Windows")
    add_definitions(-DWIN32)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "OS: Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "OS: MacOS")
else()
    message(FATAL_ERROR "Unknow OS: ${CMAKE_SYSTEM_NAME}")
endif()

# 创建编译选项
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Using MSVC compiler")
    set(CMAKE_CXX_FLAGS_DEBUG "/utf-8 /Zi /Od /EHSc")
    set(CMAKE_CXX_FLAGS_RELEASE "/utf-8 /O2 /GL /EHSc")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC compiler")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wformat")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Using Clang compiler")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wformat")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
else()
    message(FATAL_ERROR "Unknow Compile: ${CMAKE_CXX_COMPILER_ID}")
endif()

add_subdirectory(imgui_extends)
add_subdirectory(wow_common)
# add_subdirectory(wow_ui)
# add_subdirectory(wow_socket)
# add_subdirectory(wow_subprocess)
# add_subdirectory(wow_example)
