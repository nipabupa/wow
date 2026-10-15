project(wow_app VERSION 1.0)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/wow_app.cpp
    ${PROJECT_SOURCE_DIR}/wow_dialog.cpp
    ${PROJECT_SOURCE_DIR}/wow_thread.cpp
    ${PROJECT_SOURCE_DIR}/wow_theme.cpp
)

add_library(wow_app STATIC ${SOURCES})
target_include_directories(wow_app PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(wow_app imgui wow_common)
