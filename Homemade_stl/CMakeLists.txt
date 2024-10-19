cmake_minimum_required(VERSION 3.29)
project(Homemade_stl)

set(CMAKE_CXX_STANDARD 20)

add_executable(Homemade_stl main.cpp
        linkedList.h
        queue.h
        stack.h)
