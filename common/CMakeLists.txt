project(wow_common VERSION 1.0)

find_package(spdlog QUIET)
if(NOT spdlog_FOUND)
    message(STATUS "system spdlog not found")
    if(ENABLE_NETWORK)
        FetchContent_Declare(
            spdlog
            GIT_REPOSITORY https://gitee.com/nipabupa/spdlog.git
            GIT_TAG        v1.17.0
            GIT_SHALLOW    TRUE
        )
        FetchContent_MakeAvailable(spdlog)
        message(STATUS "network spdload founded")
    else()
        message(STATUS "local spdlog config...")
        add_library(spdlog STATIC IMPORTED)
        set_target_properties(spdlog PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${SPDLOG_DIR}/include
            IMPORTED_LOCATION ${SPDLOG_LIB}
        )
        message(STATUS "local spdlog founded")
    endif()
else()
    message(STATUS "system spdlog founded")
endif()

set(SOURCES
    ${PROJECT_SOURCE_DIR}/wow_utils.cpp
)

# wow_common
add_library(wow_common STATIC ${SOURCES})
target_include_directories(wow_common PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(wow_common PRIVATE wow_flags)  # 编译参数不传递
target_link_libraries(wow_common PUBLIC spdlog::spdlog)
