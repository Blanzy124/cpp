# sesion/CMakeLists.txt

set(SAVE_CONTROLLER_SRC
    save_controller.cpp
)

add_library(save_controllerLib ${SAVE_CONTROLLER_SRC})

target_include_directories(save_controllerLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(save_controllerLib PUBLIC
    nlohmann_json::nlohmann_json
)