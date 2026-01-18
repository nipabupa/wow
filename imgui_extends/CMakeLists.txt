project(imgui VERSION 1.0)

# 自定义目录
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/../deps/imgui)
set(IMPLOT_DIR ${PROJECT_SOURCE_DIR}/../deps/implot)
set(GLFW_DIR ${PROJECT_SOURCE_DIR}/../deps/glfw)

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
# IMPLOT
set(IMPLOT_SOURCES
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_items.cpp
)

file(GLOB_RECURSE IMGUI_EXTENDS_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

# GLFW
add_library(glfw SHARED IMPORTED)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(glfw PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${GLFW_DIR}/include
        IMPORTED_IMPLIB ${GLFW_DIR}/lib/vs-2022/glfw3dll.lib
        IMPORTED_LOCATION ${GLFW_DIR}/lib/vs-2022/glfw3.dll
    )
else()
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set_target_properties(glfw PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${GLFW_DIR}/include
            IMPORTED_IMPLIB ${GLFW_DIR}/lib/mingw64/glfw3dll.lib
            IMPORTED_LOCATION ${GLFW_DIR}/lib/ming264/glfw3.dll
        )
    else()
        set_target_properties(glfw PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${GLFW_DIR}/include
            IMPORTED_LOCATION ${GLFW_DIR}/lib/libglfw.so
        )
    endif()
endif()

# wow_common
add_library(imgui SHARED
    ${IMGUI_SOURCES}
    ${IMGUI_EXTENDS_SOURCES}
    $<$<BOOL:BUILD_IMPLOT>:${IMPLOT_SOURCES}>
)
target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${PROJECT_SOURCE_DIR}
    $<$<BOOL:BUILD_IMPLOT>:${IMPLOT_DIR}>
)
target_link_libraries(imgui glfw)
