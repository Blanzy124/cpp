# sesion/CMakeLists.txt

set(SESSION_SRC
    sesion.cpp
)

add_library(sesionLib PUBLIC ${SESSION_SRC})

target_include_directories(sesionLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)