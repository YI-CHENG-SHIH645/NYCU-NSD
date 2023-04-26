cmake_minimum_required(VERSION 3.9)
project(recommender_system)
set(CMAKE_CXX_STANDARD 17)

find_package(pybind11 REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED)
find_package(GTest REQUIRED)
list(APPEND third_party
  Eigen3::Eigen;
  Boost::boost;
  pybind11::module;
)

add_subdirectory(src)
add_subdirectory(tests)
