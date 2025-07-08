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

add_executable(opc-ua-project ${SOURCES})

target_link_libraries(opc-ua-project PRIVATE open62541)
