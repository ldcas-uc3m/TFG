add_library(Memory STATIC "")
add_library(CPU STATIC "")

target_include_directories(Memory PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(CPU PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

add_subdirectory(memory)
add_subdirectory(cpu)

add_executable(tfg "main.cpp")
target_link_libraries(tfg PUBLIC Memory CPU)

include_directories("cpu" "memory" "parser")