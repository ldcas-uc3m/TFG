target_link_libraries(
    Compiler

    PRIVATE
        nlohmann_json
    )


target_sources (
    Compiler

    PUBLIC
        compiler.hpp
    PRIVATE
        compiler.cpp
)
