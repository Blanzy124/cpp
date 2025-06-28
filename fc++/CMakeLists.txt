cmake_minimum_required(VERSION 3.20)
project(async4)

cmake_policy(SET CMP0167 NEW)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

set(SOURCES
	serverConecction.cpp
	httpPerform.cpp
	certificades.hpp
)

set(VCPKG_MANIFEST_MODE ON)

add_executable(async4 ${SOURCES})


target_link_libraries(async4 PRIVATE 
	Boost::boost 
	Boost::system
	OpenSSL::SSL
	OpenSSL::Crypto
	
	)

