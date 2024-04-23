add_executable(test "main.cpp")

# link libraries
target_link_libraries(test PUBLIC Memory CPU Exceptions Lib)
include_directories(
    "${CMAKE_SOURCE_DIR}/src/cpu"
    "${CMAKE_SOURCE_DIR}/src/memory"
    "${CMAKE_SOURCE_DIR}/src/parser"
    "${CMAKE_SOURCE_DIR}/src/exceptions"
    "${CMAKE_SOURCE_DIR}/src/lib"
)

