# /**
#  * @file CMakeLists.txt
#  * @brief CMake configuration for the opc-ua-project.
#  *
#  * This file configures the build system for the OPC UA project using CMake.
#  * It sets the C++ standard, includes the open62541 library, and defines targets for the server and client executables.
#  *
#  * - Requires CMake version 3.16 or higher
#  * - Uses C++20 standard
#  * - Adds open62541 as a subdirectory
#  * - Builds two executables: my_opcua_server and my_opcua_client
#  */
cmake_minimum_required(VERSION 3.16)

project(opc-ua-project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(UA_ENABLE_AMALGAMATION ON CACHE BOOL "" FORCE)
set(UA_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/open62541)

include_directories(
	include
	external/open62541/include
	external/open62541/build
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(my_opcua_server src/server.cpp)
target_link_libraries(my_opcua_server PRIVATE open62541)

add_executable(my_opcua_client src/client.cpp)
target_link_libraries(my_opcua_client PRIVATE open62541)
