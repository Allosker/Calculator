cmake_minimum_required(VERSION 4.3)
project(untitled1)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled1 main.cpp
        str_convertions.hpp
        parser.hpp
        types.hpp
        interpreter.hpp
        preprocessor.hpp)
