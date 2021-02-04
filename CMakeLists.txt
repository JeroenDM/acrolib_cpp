cmake_minimum_required(VERSION 3.0.0)
project(acrolib VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -pedantic)

include(CTest)
enable_testing()

find_package(Eigen3 REQUIRED)

include_directories(
    include
    extern
    ${EIGEN3_INCLUDE_DIRS}
)

# Library
add_library(acrolib SHARED
    src/sampling.cpp
    src/data_loggers.cpp
    src/dispersion.cpp
)

# Testing
add_executable(test_sampling test/test_sampling.cpp)
target_link_libraries(test_sampling  acrolib)
add_test(sampling test_sampling)

add_executable(test_data_loggers test/test_data_loggers.cpp)
target_link_libraries(test_data_loggers  acrolib)
add_test(data_loggers test_data_loggers)

add_executable(test_math test/test_math.cpp)
target_link_libraries(test_math  acrolib)
add_test(math test_math)

add_executable(test_dispersion test/test_dispersion.cpp)
target_link_libraries(test_dispersion  acrolib)
add_test(dispersion test_dispersion)
