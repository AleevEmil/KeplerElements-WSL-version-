cmake_minimum_required(VERSION 3.10)
project(OrbitLib)


if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -g)
endif()

find_package(Eigen3 REQUIRED)

add_subdirectory(src)

add_executable(orbit_test tests/main.cpp)
target_link_libraries(orbit_test PRIVATE ${PROJECT_NAME})