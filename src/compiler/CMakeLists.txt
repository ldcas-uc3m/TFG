target_link_libraries(Compiler PRIVATE nlohmann_json)  # dependency


target_sources (
    Compiler

    PUBLIC
        compiler.hpp
    PRIVATE
        compiler.cpp
        parser/parser.hpp
        parser/parser.cpp
)
