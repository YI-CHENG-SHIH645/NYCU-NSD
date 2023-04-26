file(GLOB HEADER_FILES *.h)
file(GLOB CPP_FILES *.cpp)
list(FILTER CPP_FILES EXCLUDE REGEX ".*/main.cpp")

add_library(recommender ${HEADER_FILES} ${CPP_FILES})
add_executable(main main.cpp)

target_include_directories(recommender INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
message(Eigen3::Eigen)

target_link_libraries(recommender ${third_party})
target_link_libraries(main ${third_party} recommender)
