cmake_minimum_required(VERSION 3.8)
project(Lista4)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Tree/Tree.cpp Tree/Tree.h Tree/Node/Node.cpp Tree/Node/Node.h Generator/ExpressionGenerator.cpp Generator/ExpressionGenerator.h God/GodOfTheTrees.cpp God/GodOfTheTrees.h)
add_executable(Lista4 ${SOURCE_FILES})