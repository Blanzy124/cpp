# connection/CMakeLists.txt

set(CONNECTION_SRC
    httpPerform.cpp
    serverConecction.cpp
)

add_library(connectionLib STATIC ${CONNECTION_SRC})

target_include_directories(connection PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)