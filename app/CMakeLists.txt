project(wow_app VERSION 1.0)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/wow_app.cpp
    ${PROJECT_SOURCE_DIR}/wow_config.cpp
    ${PROJECT_SOURCE_DIR}/wow_theme.cpp
    ${PROJECT_SOURCE_DIR}/wow_widgets.cpp
    ${PROJECT_SOURCE_DIR}/wow_dialog.cpp
    ${PROJECT_SOURCE_DIR}/wow_thread.cpp
)

add_library(wow_app STATIC ${SOURCES})
target_include_directories(wow_app PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(wow_app PRIVATE wow_flags)  # 编译参数不传递
target_link_libraries(wow_app PUBLIC imgui wow_common)

if(ENABLE_IMPLOT)
    target_compile_definitions(wow_app PRIVATE ENABLE_IMPLOT)
endif()

# 寻找系统库
find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    message(STATUS "nlohmann_json not found")
    if(ENABLE_FROM_NETWORK)
        # 网络下载
        FetchContent_Declare(
            nlohmann_json
            GIT_REPOSITORY https://gitee.com/nipabupa/nlohmann-json.git
            GIT_TAG        v3.12.0
        )
        set(JSON_BuildTests OFF CACHE BOOL "" FORCE)
        set(JSON_Install    OFF CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(nlohmann_json)
        target_link_libraries(wow_app PUBLIC nlohmann_json)
    else()
        # Windows直接使用hpp头文件
        target_include_directories(wow_app PUBLIC ${JSON_DIR})
    endif()
endif()

