cmake_minimum_required(VERSION 3.10.0)

project(wow VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 生成compile_command.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# unicode支持
add_definitions(-DUNICODE -D_UNICODE)
# add_definitions(-DWIN32 -D_WIN32)
set(CMAKE_CXX_FLAGS "-O3 -DNDEBUG") # Release 模式
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wformat") # Debug 模式
# 自定义目录
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/lib/imgui)
set(IMPLOT_DIR ${PROJECT_SOURCE_DIR}/lib/implot)
set(GLFW_DIR ${PROJECT_SOURCE_DIR}/lib/glfw)
set(SPDLOG_DIR ${PROJECT_SOURCE_DIR}/lib/spdlog)
# 头文件
include_directories(
    ${GLFW_DIR}/include
    ${SPDLOG_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${IMPLOT_DIR}
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
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_demo.cpp
    ${IMPLOT_DIR}/implot_items.cpp
)
file(GLOB_RECURSE GUI src/gui/*.cpp)
file(GLOB_RECURSE COMMON src/common/*.cpp)
file(GLOB_RECURSE SERVICE src/tests/*.cpp)
file(GLOB_RECURSE TESTS src/tests/*.cpp)
# 创建二进制文件
add_executable(wow ${GUI} ${COMMON} ${SERVICE} ${IMGUI_BACKDENDS_SOURCES} ${IMGUI_SOURCES})
# add_executable(wow-test ${TESTS} ${COMMON} ${SERVICE})
# 链接GLFW OPenGL
if(WIN32)
    target_link_libraries(wow ${GLFW_DIR}/lib/libglfw3.a opengl32 gdi32 shell32)
else()
    target_link_libraries(wow ${GLFW_DIR}/lib/libglfw3.a GL)
endif()
# 链接spdlog
target_link_libraries(wow ${SPDLOG_DIR}/lib/libspdlog.a)
