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
    # ${PROJECT_SOURCE_DIR}/imgui_freetype.cpp
    ${PROJECT_SOURCE_DIR}/imgui_extends.cpp
)

# IMPLOT
set(IMPLOT_SOURCES
    ${PROJECT_SOURCE_DIR}/implot.cpp
    ${PROJECT_SOURCE_DIR}/implot_items.cpp
)

find_package(glfw QUIET)
if(NOT glfw_FOUND)
    if(BUILD_FROM_NETWORK)
        FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://gitee.com/nipabupa/glfw.git
            GIT_TAG        3.5.1
            GIT_SHALLOW    TRUE
        )
        set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(glfw)
    else()
        add_library(glfw STATIC IMPORTED)
        if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
            # windows 可以MSVC与Mingw64
            if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
                set(GLFW_LIB ${GLFW_DIR}/lib-vc2022/glfw3_mt.lib)
            else()
                set(GLFW_LIB ${GLFW_DIR}/lib-mingw-w64/libglfw3.a)
            endif()
        else()
            set(GLFW_LIB ${GLFW_DIR}/lib/libglfw3.lib)
        endif()
        set_target_properties(glfw PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${GLFW_DIR}/include
            IMPORTED_LOCATION ${GLFW_LIB}
        )
    endif()
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
