cmake_minimum_required(VERSION 3.10)

project(test)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(src/headers)


set(SOURCES main.cpp 
	src/code/objectList.cpp
	src/code/Groups.cpp
)

add_executable(test ${SOURCES})
