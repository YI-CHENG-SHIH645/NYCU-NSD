cmake_minimum_required(VERSION 3.20)
project(YI_CHENG_SHIH645)

set(CMAKE_CXX_STANDARD 14)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(pybind11 CONFIG)
include_directories(${pybind11_INCLUDE_DIR})

set(BLAS /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib/libblas.tbd)
set(MKL_INCLUDE_DIR /opt/intel/oneapi/mkl/2021.4.0/include)
include_directories(${MKL_INCLUDE_DIR})

pybind11_add_module(_matrix matrix.cpp)
add_compile_options(-O3 -Wall -std=c++11)
add_executable(main matrix.cpp)

target_link_libraries(main ${PYTHON_LIBRARIES})
target_link_libraries(main ${BLAS})
