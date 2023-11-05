#ifndef ALU_HPP
#define ALU_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <stdexcept>

#include "interpreter/ast.hpp"
#include "../exceptions.hpp"



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


        /* OPERATORS */

        const Token sum (const std::vector<Token> & v) {
            
            // check parameters
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            if (v[0].type != token_type::INM || v[1].type != token_type::INM) {
                throw std::invalid_argument("Invalid argument type");
            }

            int result = stoi(v[0].string) + stoi(v[1].string);
            return Token {std::to_string(result), token_type::INM};
        }


        /* REGISTERS */

        const Token get_register (const std::vector<Token> & v) {
            if (v.size() != 1) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            if (v[0].type != token_type::REG) {
                throw std::invalid_argument("Invalid argument type");
            }


            std::uint32_t result;
            try {
                result = _rf[v[0].string];
            }
            catch (std::out_of_range e) {
                throw LUISPDAException("Register " + v[0].string + " not found.");
            }

            return Token {std::to_string(result), token_type::INM};
        }


        const Token set_register (const std::vector<Token> & v) {
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            if (v[0].type != token_type::REG || v[1].type != token_type::INM) {
                throw std::invalid_argument("Invalid argument type");
            }

            std::uint32_t value = static_cast<std::uint32_t>(stoi(v[1].string));
            _rf[v[0].string] = value;

            return Token {std::to_string(value), token_type::INM};
        }



    private:
        RegisterFile & _rf;

};

#endif