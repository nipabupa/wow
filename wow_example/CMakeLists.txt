project(wow_example VERSION 1.0)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

# wow_ui
add_executable(wow_example ${SOURCES})
target_link_libraries(wow_example wow_common imgui wow_ui)

install(TARGETS wow_example
    RUNTIME DESTINATION lib
)
