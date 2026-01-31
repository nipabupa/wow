add_library(imgui SHARED IMPORTED)
add_library(wow_common SHARED IMPORTED)
add_library(wow_ui SHARED IMPORTED)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set_target_properties(imgui PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include
        IMPORTED_IMPLIB ${PROJECT_SOURCE_DIR}/lib/imgui.lib
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/imgui.dll
    )
    set_target_properties(wow_common PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include
        IMPORTED_IMPLIB ${PROJECT_SOURCE_DIR}/lib/wow_common.lib
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/wow_common.dll
    )
    set_target_properties(wow_ui PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include
        IMPORTED_IMPLIB ${PROJECT_SOURCE_DIR}/lib/wow_ui.lib
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/wow_ui.dll
        INTERFACE_LINK_LIBRARIES "imgui;wow_common"
    )
else()
    set_target_properties(imgui PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/imgui.so
    )
    set_target_properties(wow_common PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/wow_common.so
    )
    set_target_properties(wow_ui PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/wow_ui.so
        INTERFACE_LINK_LIBRARIES "imgui;wow_common"
    )
endif()
