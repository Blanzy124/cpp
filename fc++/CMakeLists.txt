cmake_minimum_required(VERSION 3.20)
project(async4)

cmake_policy(SET CMP0167 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") #this dete
    add_compile_options(/bigobj)
endif()
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_subdirectory(connection)
add_subdirectory(config)
add_subdirectory(session)

#set(SOURCES
#	main.cpp
#)


set(VCPKG_MANIFEST_MODE OFF)

add_executable(async4 main.cpp)

target_include_directories(async4 PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${Boost_INCLUDE_DIRS}
)

target_link_libraries(async4 PRIVATE
	configLib
	connectionLib
	sessionLib
	Boost::system
	OpenSSL::SSL
	OpenSSL::Crypto
	fmt::fmt-header-only
	nlohmann_json::nlohmann_json
)
