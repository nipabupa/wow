set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("Using GCC compiler")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wformat")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message("Using Clang compiler")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wformat")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
else()
    message(FATAL_ERROR "Unknow Compile: ${CMAKE_CXX_COMPILER_ID}")
endif()

# GLFW
add_library(glfw SHARED IMPORTED)
set_target_properties(glfw PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${GLFW_DIR}/include
    IMPORTED_LOCATION ${GLFW_DIR}/lib/libglfw.so
)
# SPDLOG
add_library(spdlog STATIC IMPORTED)
set_target_properties(spdlog PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${SPDLOG_DIR}/include
    IMPORTED_LOCATION ${SPDLOG_DIR}/lib/libspdlog.a
)

add_library(imgui SHARED ${IMGUI_SOURCES} {IMPLOT_SOURCES})
target_include_directories(imgui PUBLIC
    ${IMGUI}
    ${IMGUI}/backends
    $<$<BUILD_IMPLOT:ON>:${IMGUI_EXTENDS}>>
)

add_library(wow_utils SHARED ${WOW_UTILS_SOURCES})
target_include_directories(wow_utils PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(wow_utils spdlog)

add_library(wow_ui SHARED ${WOW_UI_SOURCES})
target_link_libraries(wow_ui wow_utils imgui glfw GL)

# add_library(wow_socket SHARED ${WOW_SOCKET_SOURCES})
# target_link_libraries(wow_socket wow_utils)

# add_library(wow_serial SHARED ${WOW_SERIAL_SOURCES})
# target_link_libraries(wow_serial wow_utils)

# add_library(wow_subprocess SHARED ${WOW_SUBPROCESS_SOURCES})
# target_link_libraries(wow_subprocess wow_utils)
