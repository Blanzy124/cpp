# sesion/CMakeLists.txt

set(SESSION_SRC
    session.cpp
)

add_library(sessionLib ${SESSION_SRC})

target_include_directories(sessionLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)