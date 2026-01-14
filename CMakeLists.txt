cmake_minimum_required(VERSION 4.0)

project(wow VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 生成compile_command.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 自定义目录
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/deps/imgui)
set(IMPLOT_DIR ${PROJECT_SOURCE_DIR}/deps/implot)
set(GLFW_DIR ${PROJECT_SOURCE_DIR}/deps/glfw)
set(STB_DIR ${PROJECT_SOURCE_DIR}/deps/stb)
set(SPDLOG_DIR ${PROJECT_SOURCE_DIR}/deps/spdlog)

# 代码文件
# IMGUI
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
)
# IMGUI Demo
set(IMGUI_DEMO_SOURCE ${IMGUI_DIR}/imgui_demo.cpp)
# IMPLOT
set(IMPLOT_SOURCES
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_items.cpp
)
# IMPLOT Demo
set(IMGUI_DEMO_SOURCE ${IMPLOT_DIR}/implot_demo.cpp)

file(GLOB_RECURSE WOW_UI_SOURCES src/wow_ui/*.cpp)
file(GLOB_RECURSE WOW_UTILS_SOURCES src/wow_utils/*.cpp)
file(GLOB_RECURSE WOW_SUBPROCESS_SOURCES src/wow_subprocess/*.cpp)
file(GLOB_RECURSE WOW_SOCKET_SOURCES src/wow_socket/*.cpp)
file(GLOB_RECURSE WOW_SERIAL_SOURCES src/wow_serial/*.cpp)

# 选择对应平台
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "OS: Windows")
    include("win.cmake")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "OS: Linux")
    include("linux.cmake")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "OS: MacOS")
    include("macos.cmake")
else()
    message(ERROR "Unknow OS")
endif()
