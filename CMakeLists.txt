cmake_minimum_required(VERSION 3.10)
project(STL)

add_definitions(-std=c++17)

add_executable(STL main.cpp deque.hpp memory.hpp)