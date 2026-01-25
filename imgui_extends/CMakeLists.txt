project(imgui VERSION 1.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
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
    ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
    $<$<BOOL:BUILD_DEMO>:${IMGUI_DIR}/imgui_demo.cpp>

)
# IMPLOT
set(IMPLOT_SOURCES
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_items.cpp
    $<$<BOOL:BUILD_DEMO>:${IMPLOT_DIR}/implot_demo.cpp>
)

file(GLOB_RECURSE IMGUI_EXTENDS_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

# GLFW
add_library(glfw SHARED IMPORTED)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(GLFW_LIB ${GLFW_DIR}/lib-vc2022/glfw3_mt.lib)
else()
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(GLFW_LIB ${GLFW_DIR}/lib-mingw-w64/libglfw3.a)
    else()
        set(GLFW_LIB ${GLFW_DIR}/lib/libglfw3.a)
    endif()
endif()

set_target_properties(glfw PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${GLFW_DIR}/include
    IMPORTED_LOCATION ${GLFW_LIB}
)

# imgui_extends
add_library(imgui SHARED
    ${IMGUI_SOURCES}
    ${IMGUI_EXTENDS_SOURCES}
    $<$<BOOL:BUILD_IMPLOT>:${IMPLOT_SOURCES}>
)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${IMGUI_DIR}/misc/cpp
    ${PROJECT_SOURCE_DIR}
    $<$<BOOL:BUILD_IMPLOT>:${IMPLOT_DIR}>
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(imgui glfw opengl32 gdi32 shell32)
else()
    target_link_libraries(imgui glfw GL)
endif()

install(TARGETS imgui
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION lib
)

install(FILES
    ${IMGUI_DIR}/imgui.h
    ${IMGUI_DIR}/imconfig.h
    ${IMGUI_DIR}/misc/cpp/imgui_stdlib.h
    DESTINATION include)

install(DIRECTORY ${GLFW_DIR}/include/GLFW
    DESTINATION include)
