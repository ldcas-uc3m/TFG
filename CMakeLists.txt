cmake_minimum_required(VERSION 3.22)

project(tfg LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
add_compile_options(-Wall -Werror -Wextra -pedantic -pedantic-errors -fPIC)


add_subdirectory("src")