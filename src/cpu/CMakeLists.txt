project(CPU)

target_sources ( CPU
    PUBLIC
        interpreter/interpreter.hpp
        register_file.hpp
        alu.hpp
    PRIVATE
        interpreter/interpreter.cpp
        interpreter/ast.hpp
        interpreter/ast.cpp
        interpreter/reader.hpp
        interpreter/reader.cpp
        alu.cpp
)
