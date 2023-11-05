#ifndef ALU_HPP
#define ALU_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

#include "interpreter/ast.hpp"



using lisp_function = std::function<const Token (const std::vector<Token> &)>;


class ALU {

    public:
        ALU(RegisterFile & rf) : _rf {rf} {
            _rf = rf;
        }



        // map of function names and function pointers

        #define ALU_FUNCTION(name)  [this] (const std::vector<Token> & v) -> const Token { return this->name(v); }  // we need a lambda wrapper for the functions

        const std::unordered_map<std::string, lisp_function> repl_env {
            { "+", ALU_FUNCTION(sum) },
            { "reg", ALU_FUNCTION(get_register) },
            { "reg!", ALU_FUNCTION(set_register) }
        };



        const Token sum (const std::vector<Token> & v) {

            if (v.size() != 2) {
                throw;  // TODO: exception
            }

            int result = stoi(v[0].string) + stoi(v[1].string);
            return Token {std::to_string(result), token_type::INM};
        }


        const Token get_register (const std::vector<Token> & v) {
            if (v.size() != 1) {
                throw;  // TODO: exception
            }

            std::uint32_t result;
            try {
                result = _rf[v[0].string];
            }
            catch (std::out_of_range e) {
                std::cout << "Register not found" << std::endl;
                throw;  // TODO: exception
            }

            return Token {std::to_string(result), token_type::INM};
        }
        
        
        const Token set_register (const std::vector<Token> & v) {
            if (v.size() != 2) {
                throw;  // TODO: exception
            }

            std::uint32_t value = static_cast<std::uint32_t>(stoi(v[1].string));
            try {
                _rf[v[0].string] = value;
            }
            catch (std::out_of_range e) {
                std::cout << "Register not found" << std::endl;
                throw;  // TODO: exception
            }

            return Token {std::to_string(value), token_type::INM};
        }



    private:
        RegisterFile & _rf;


};

#endif