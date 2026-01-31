project(wow_ui VERSION 1.0)

# 自定义目录
set(STB_DIR ${PROJECT_SOURCE_DIR}/../deps/stb)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

# wow_ui
add_library(wow_ui SHARED ${SOURCES})
target_include_directories(wow_ui PUBLIC ${PROJECT_SOURCE_DIR} ${STB_DIR})
target_compile_definitions(wow_ui PRIVATE WOW_UI_EXPORT)
target_link_libraries(wow_ui imgui wow_common)

install(TARGETS wow_ui
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION lib
)

install(FILES wow_ui.h
    DESTINATION include)
