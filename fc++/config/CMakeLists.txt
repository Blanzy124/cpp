# connection/CMakeLists.txt

set(CONFIG_SRC
    config.cpp
)

add_library(configLib ${CONFIG_SRC})

target_include_directories(configLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)