# connection/CMakeLists.txt

set(CONNECTION_SRC
    targets.cpp
    request_parser.cpp
    serverConnection.cpp
    httpPerform.cpp
)

add_library(connectionLib ${CONNECTION_SRC})

target_include_directories(connectionLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)