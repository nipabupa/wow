project(wow_common)

set(SPDLOG_DIR ${PROJECT_SOURCE_DIR}/../deps/spdlog)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(SPDLOG_LIB ${SPDLOG_DIR}/lib/spdlog.lib)
else()
    set(SPDLOG_LIB ${SPDLOG_DIR}/lib/libspdlog.a)
endif()

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

# spdlog
add_library(spdlog STATIC IMPORTED)
set_target_properties(spdlog PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${SPDLOG_DIR}/include
    IMPORTED_LOCATION ${SPDLOG_LIB}
)

# wow_common
add_library(wow_common SHARED ${SOURCES})
target_include_directories(wow_common PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(wow_common spdlog)
