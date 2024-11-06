cmake_minimum_required(VERSION 3.29)
project(CS202_HW2)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS202_HW2
        Heap.h
        least5.cpp
        prefixsubarray.cpp
        game.cpp
        subarray.cpp
        AVL_Tree.cpp
        AVL_Tree.h
        AVL_Node.h
)
