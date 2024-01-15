# build libraries
add_library(Memory STATIC)
add_library(CPU STATIC)
add_library(Exceptions STATIC)

target_include_directories(Memory PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(CPU PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(Exceptions PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(memory)
add_subdirectory(cpu)
add_subdirectory(exceptions)


# add compilation target
add_executable(${PROJECT_NAME} "main.cpp")

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC Memory CPU Exceptions)
include_directories("cpu" "memory" "parser" "exceptions")