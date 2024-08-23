cmake_minimum_required(VERSION 3.22)

project(interpreter VERSION 1.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

add_library(interpreter src/vector.c)

add_executable(vector_test src/vector_test.c)
target_link_libraries(vector_test interpreter)
