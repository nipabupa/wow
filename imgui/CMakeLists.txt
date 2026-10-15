project(imgui VERSION 1.0)

# 代码文件
set(IMGUI_SOURCES
    ${PROJECT_SOURCE_DIR}/imgui_impl_opengl3.cpp
    ${PROJECT_SOURCE_DIR}/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/imgui_stdlib.cpp
    ${PROJECT_SOURCE_DIR}/imgui.cpp
    ${PROJECT_SOURCE_DIR}/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/imgui_freetype.cpp
    ${PROJECT_SOURCE_DIR}/imgui_extends.cpp
)

# IMPLOT
set(IMPLOT_SOURCES
    ${PROJECT_SOURCE_DIR}/implot.cpp
    ${PROJECT_SOURCE_DIR}/implot_items.cpp
)

# Linux自行安装glfw开发库, Window使用预编译组件vc2022
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # windows 可以MSVC与Mingw64
    add_library(glfw STATIC IMPORTED)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(GLFW_LIB ${GLFW_DIR}/lib-vc2022/glfw3_mt.lib)
    else()
        set(GLFW_LIB ${GLFW_DIR}/lib-mingw-w64/libglfw3.a)
    endif()
    set_target_properties(glfw PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${GLFW_DIR}/include
        IMPORTED_LOCATION ${GLFW_LIB}
    )
endif()

add_library(imgui STATIC
    ${IMGUI_SOURCES}
    $<$<BOOL:BUILD_IMPLOT>:${IMPLOT_SOURCES}>
)

target_include_directories(imgui PUBLIC
    ${PROJECT_SOURCE_DIR}
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(imgui glfw opengl32 gdi32 shell32)
else()
    target_link_libraries(imgui glfw GL)
endif()
