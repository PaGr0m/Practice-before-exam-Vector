cmake_minimum_required(VERSION 3.15)
project(Practice_before_exam_Vector)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") # CMake already contains W3 in its flags
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif ()

add_executable(smoke smoke_test.cpp vector.hpp utils.hpp)
