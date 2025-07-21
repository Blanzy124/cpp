# connection/CMakeLists.txt

set(CONNECTION_SRC
    httpPerform.cpp
    serverConnection.cpp
)

add_library(connectionLib ${CONNECTION_SRC})

target_include_directories(connectionLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)