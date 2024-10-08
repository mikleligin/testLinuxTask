cmake_minimum_required(VERSION 3.10)

project(test)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(src/headers)
find_package(SQLite3 REQUIRED)
if(SQLite3_FOUND)
    include_directories(${SQLite3_INCLUDE_DIRS}) # Добавляем директорию заголовков
    message(STATUS "Found SQLite3: ${SQLite3_LIBRARIES}")
else()
    message(FATAL_ERROR "SQLite3 not found")
endif()

set(SOURCES main.cpp 
	src/code/objectList.cpp
	src/code/Groups.cpp
	src/code/dbSql.cpp
)

add_executable(test ${SOURCES})
target_link_libraries(test PRIVATE ${SQLite3_LIBRARIES})
