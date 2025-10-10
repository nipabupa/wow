cmake_minimum_required(VERSION 3.10.0)

project(wow VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 生成compile_command.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# unicode支持
add_definitions(-DUNICODE -D_UNICODE)
# DEBUG
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-O3 -DNDEBUG") # Release 模式
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wformat") # Debug 模式
# 特性控制
set(WIN32 false)
set(WOW_LOG true)
set(WOW_SOCKET true)
set(WOW_SHELL true)
set(WOW_SERIAL true)
set(WOW_PLOT true)
# windows
if(WIN32)
add_definitions(-DWIN32)
endif()
# 日志特性支持
if(WOW_LOG)
add_definitions(-DWOW_LOG)
endif()
# SOCKET特性支持
if(WOW_SOCKET)
add_definitions(-DWOW_SOCKET)
endif()
# Shell特性支持
if(WOW_SHELL)
add_definitions(-DWOW_SHELL)
endif()
# 串口特性支持
if(WOW_SERIAL)
add_definitions(-DWOW_SERIAL)
endif()
# 自定义目录
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/lib/imgui)
set(GLFW_DIR ${PROJECT_SOURCE_DIR}/lib/glfw)
# 头文件
include_directories(
    ${GLFW_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${PROJECT_SOURCE_DIR}/include
)
# 窗口与OpenGL代码
set(IMGUI_BACKDENDS_SOURCES
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
)
# IMGUI代码
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    # ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

if(WOW_LOG)
    set(SPDLOG_DIR ${PROJECT_SOURCE_DIR}/lib/spdlog)
    include_directories(${SPDLOG_DIR}/include)
endif()

if(WOW_PLOT)
    set(IMPLOT_DIR ${PROJECT_SOURCE_DIR}/lib/implot)
    include_directories(${IMPLOT_DIR})
    list(APPEND IMGUI_SOURCES
        ${IMPLOT_DIR}/implot.cpp
        # ${IMPLOT_DIR}/implot_demo.cpp
        ${IMPLOT_DIR}/implot_items.cpp
    )
endif()

file(GLOB_RECURSE WOW src/wow/*.cpp)
file(GLOB_RECURSE COMMON src/common/*.cpp)
file(GLOB_RECURSE SRC src/*.cpp)
# 创建二进制文件
add_executable(wow ${WOW} ${COMMON} ${SRC} ${IMGUI_BACKDENDS_SOURCES} ${IMGUI_SOURCES})
# 链接GLFW OPenGL
if(WIN32)
    message("Link Windows")
    target_link_libraries(wow ${GLFW_DIR}/lib/libglfw3.a opengl32 gdi32 shell32)
else()
    message("Link Linux")
    target_link_libraries(wow ${GLFW_DIR}/lib/libglfw3.a GL)
endif()

if(WOW_LOG)
    message("Link spdlog")
    target_link_libraries(wow ${SPDLOG_DIR}/lib/libspdlog.a)
endif()
