#ifndef ALU_HPP
#define ALU_HPP

#include <vector>
#include <map>
#include <string>

#include "interpreter/ast.hpp"



// map of function names and function pointers
// using lisp_function = std::function<Token (*) (std::vector<Token>)>;
using lisp_function = std::function<Token (std::vector<Token>)>;

const std::map<std::string, lisp_function> repl_env {
    {"+",
    [] (std::vector<Token> v) -> Token {
        if (v.size() != 2) {
            throw;  // TODO: exception
        }
        int result = stoi(v[0].string) + stoi(v[1].string);
        return Token {std::to_string(result), token_type::INM};
    }
    // sum  // TODO: map to function, not lambda
    }
};


Token sum (std::vector<Token> v) {

    if (v.size() != 2) {
        throw;  // TODO: exception
    }

    int result = stoi(v[0].string) + stoi(v[1].string);
    return Token {std::to_string(result), token_type::INM};
}


#endif