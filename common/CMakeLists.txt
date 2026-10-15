project(wow_common VERSION 1.0)

# Linux自行安装spdlog开发库, Window使用预编译组件
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(SPDLOG_LIB ${SPDLOG_DIR}/lib/spdlog.lib)
    else()
        set(SPDLOG_LIB ${SPDLOG_DIR}/lib/libspdlog.a)
    endif()
    add_library(spdlog STATIC IMPORTED)
    set_target_properties(spdlog PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${SPDLOG_DIR}/include
        IMPORTED_LOCATION ${SPDLOG_LIB}
    )
endif()

set(SOURCES
    ${PROJECT_SOURCE_DIR}/wow_utils.cpp
)

# wow_common
add_library(wow_common STATIC ${SOURCES})
target_include_directories(wow_common PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(wow_common spdlog)
