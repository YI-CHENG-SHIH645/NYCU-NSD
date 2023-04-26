cmake_minimum_required(VERSION 3.20)
project(q2)
add_subdirectory(pybind11)

set(CMAKE_CXX_STANDARD 11)

pybind11_add_module(_vector q2.cpp)
