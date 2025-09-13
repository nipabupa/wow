cmake_minimum_required(VERSION 3.31.0)

project(wow VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# unicode支持
add_definitions(-DUNICODE -D_UNICODE)
# set(CMAKE_CXX_FLAGS "-O3 -DNDEBUG") # Release 模式
set(CMAKE_CXX_FLAGS_DEBUG "-g") # Debug 模式

# 自定义目录
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/lib/imgui)

include_directories(
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${PROJECT_SOURCE_DIR}/include
)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

if(${WIN32})
    set(IMGUI_BACKDENDS_SOURCES
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
    )
else()
    set(IMGUI_BACKDENDS_SOURCES
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    )
    target_link_libraries(wow GL glfw3)
endif()
# src目录下所有cpp文件
file(GLOB_RECURSE SOURCES src/*.cpp)
# 创建二进制文件
add_executable(wow WIN32 ${SOURCES} ${IMGUI_BACKDENDS_SOURCES} ${IMGUI_SOURCES})
# 链接库
if(${WIN32})
    # 链接库
    target_link_libraries(wow opengl32 gdi32 dwmapi)
else()
    target_link_libraries(wow GL glfw3)
endif()
