# sesion/CMakeLists.txt

set(SESSION_SRC
    sesion.cpp
)

add_library(sesionLib STATIC ${SESSION_SRC})

target_include_directories(sesionLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)