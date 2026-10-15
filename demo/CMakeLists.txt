project(wow_demo VERSION 1.0)

add_executable(wow_demo
    ${PROJECT_SOURCE_DIR}/demo.cpp
    ${PROJECT_SOURCE_DIR}/imgui_demo.cpp
    $<$<BOOL:BUILD_IMPLOT>:${PROJECT_SOURCE_DIR}/implot_demo.cpp>
)

target_link_libraries(wow_demo wow_app)
