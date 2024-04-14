# create libraries
add_library(Memory INTERFACE)
add_library(CPU STATIC)
add_library(Exceptions INTERFACE)
add_library(Lib STATIC)
add_library(Compiler STATIC)

# give every library access to src/
target_include_directories(Memory INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(CPU PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(Exceptions INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(Lib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(Compiler PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# get third party libs
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# build libraries
add_subdirectory(lib)
add_subdirectory(memory)
add_subdirectory(cpu)
add_subdirectory(exceptions)
add_subdirectory(compiler)


# add compilation target
add_executable(${PROJECT_NAME} "main.cpp")

# link libraries
target_link_libraries (
    ${PROJECT_NAME}
    PUBLIC
        Memory
        CPU
        Exceptions
        Compiler
        Lib
    PRIVATE
        nlohmann_json::nlohmann_json
)

include_directories("lib" "cpu" "memory" "parser" "exceptions" "compiler")