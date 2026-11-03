project(wow_demo VERSION 1.0)

add_executable(wow_demo
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/app.cpp
)

target_include_directories(wow_demo PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(wow_demo PRIVATE wow_flags wow_app)  # 编译参数不传递
