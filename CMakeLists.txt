# CMake config
cmake_minimum_required(VERSION 3.22)

project(tfg LANGUAGES CXX)

set(JSON_BuildTests OFF CACHE INTERNAL "")

# C++ Config
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# compiler config
add_definitions(-std=c++20)
add_compile_options(-Wall -Wextra -pedantic -pedantic-errors -fPIC)


# include targets
add_subdirectory("src")
add_subdirectory("test")