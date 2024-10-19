cmake_minimum_required(VERSION 3.29)
project(CS202_HW1)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS202_HW1 main.cpp
        BST.cpp
        BST.h
        analysis.cpp
        analysis.h
        queue.h
        Node.h
        linkedList.h
)
