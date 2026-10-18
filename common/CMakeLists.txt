project(wow_common VERSION 1.0)

find_package(spdlog QUIET)
if(NOT spdlog_FOUND)
    if(BUILD_FROM_NETWORK)
        FetchContent_Declare(
            spdlog
            GIT_REPOSITORY https://gitee.com/nipabupa/spdlog.git
            GIT_TAG        v1.17.0
            GIT_SHALLOW    TRUE
        )
        FetchContent_MakeAvailable(spdlog)
    else()
        # Linux自行安装spdlog开发库, Window使用预编译组件
        if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
            add_library(spdlog STATIC IMPORTED)
            set_target_properties(spdlog PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${SPDLOG_DIR}/include
                IMPORTED_LOCATION ${SPDLOG_LIB}
            )
        else()
            find_package(spdlog)
        endif()
    endif()
endif()

set(SOURCES
    ${PROJECT_SOURCE_DIR}/wow_utils.cpp
)

# wow_common
add_library(wow_common STATIC ${SOURCES})
target_include_directories(wow_common PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(wow_common spdlog::spdlog)
