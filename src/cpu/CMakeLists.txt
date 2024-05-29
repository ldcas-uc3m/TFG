target_sources (
    CPU

    PUBLIC
        control_unit/control_unit.hpp
        register_file.hpp
        alu.hpp
    PRIVATE
        control_unit/control_unit.cpp
        control_unit/ast.hpp
        control_unit/ast.cpp
        control_unit/reader.hpp
        control_unit/reader.cpp
        alu.cpp
)
