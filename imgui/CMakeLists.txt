project(imgui VERSION 1.0)

# 代码文件
set(IMGUI_SOURCES
    ${PROJECT_SOURCE_DIR}/imgui.cpp
    ${PROJECT_SOURCE_DIR}/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/backend/imgui_impl_opengl3.cpp
    ${PROJECT_SOURCE_DIR}/backend/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
    ${PROJECT_SOURCE_DIR}/misc/freetype/imgui_freetype.cpp
    ${PROJECT_SOURCE_DIR}/wow/wow_base_widgets.cpp
    $<$<BOOL:${ENABLE_DEMO}>:${PROJECT_SOURCE_DIR}/imgui_demo.cpp>
)

# IMPLOT
set(IMPLOT_SOURCES
    ${PROJECT_SOURCE_DIR}/implot/implot.cpp
    ${PROJECT_SOURCE_DIR}/implot/implot_items.cpp
    $<$<BOOL:${ENABLE_DEMO}>:${PROJECT_SOURCE_DIR}/implot/implot_demo.cpp>
)

find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
    message(STATUS "system glfw3 not found")
    if(ENABLE_NETWORK)
        message(STATUS "network glfw3 download...")
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
        message(STATUS "network glfw3 founded")
    else()
        message(STATUS "local glfw3 config...")
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
        message(STATUS "local glfw3 founded")
    endif()
else()
    message(STATUS "system glfw3 founded")
endif()


find_package(Freetype QUIET)
if(NOT Freetype_FOUND)
    message(STATUS "system freetype not found")
    if(ENABLE_NETWORK)
        message(STATUS "network freetype download...")
        FetchContent_Declare(
            freetype
            GIT_REPOSITORY https://github.com/freetype/freetype.git
            GIT_TAG        VER-2-15-0
        )
        set(FT_WITH_ZLIB OFF CACHE BOOL "" FORCE)
        set(FT_WITH_PNG OFF CACHE BOOL "" FORCE)
        set(FT_WITH_BZIP2 OFF CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(freetype)
        message(STATUS "network freetype founded")
    endif()
else()
    message(STATUS "system freetype founded")
endif()

add_library(imgui STATIC
    ${IMGUI_SOURCES}
    $<$<BOOL:ENABLE_IMPLOT>:${IMPLOT_SOURCES}>
)

target_include_directories(imgui PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/wow
    $<$<BOOL:${ENABLE_IMPLOT}>:${PROJECT_SOURCE_DIR}/implot>
    ${PROJECT_SOURCE_DIR}/backend
    ${PROJECT_SOURCE_DIR}/misc/freetype
    ${PROJECT_SOURCE_DIR}/misc/cpp
)
# 自定义imgui配置
target_compile_definitions(imgui PUBLIC IMGUI_USER_CONFIG="wow_imconfig.h")
target_link_libraries(imgui PRIVATE wow_flags)  # 编译参数不传递
target_link_libraries(imgui PUBLIC Freetype::Freetype)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(imgui PUBLIC glfw opengl32 gdi32 shell32)
else()
    target_link_libraries(imgui PUBLIC glfw GL)
endif()
