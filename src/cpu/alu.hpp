#ifndef ALU_HPP
#define ALU_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <stdexcept>

#include "interpreter/ast.hpp"
#include "../exceptions.hpp"
#include "../memory/text.hpp"



using lisp_function = std::function<const Token (const std::vector<Token> &)>;


class ALU {

    public:
        ALU(RegisterFile & rf, Memory::text & mem_t) : _rf {rf}, _mem_t {mem_t} { }



        // map of function names and function pointers

        #define ALU_FUNCTION(func)  [this] (const std::vector<Token> & v) -> const Token { return this->func(v); }  // we need a lambda wrapper for the functions

        const std::unordered_map<std::string, lisp_function> repl_env {
            { "+", ALU_FUNCTION(sum) },
            { "reg", ALU_FUNCTION(get_register) },
            { "reg!", ALU_FUNCTION(set_register) },
            { "pc", ALU_FUNCTION(get_pc) },
            { "pc!", ALU_FUNCTION(set_pc) }
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


            int result = stoi(v[0].value) + stoi(v[1].value);

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
                result = _rf[v[0].value];
            }
            catch (std::out_of_range e) {
                throw LUISPDAException("Register " + v[0].value + " not found.");
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

            std::uint32_t value = static_cast<std::uint32_t>(stoi(v[1].value));
            _rf[v[0].value] = value;

            return Token {std::to_string(value), token_type::INM};
        }


        /* PROGRAM COUNTER */

        const Token get_pc (const std::vector<Token> & v) {
            if (v.size() != 0) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            return Token {std::to_string(_rf.pc), token_type::INM};
        }

        const Token set_pc (const std::vector<Token> & v) {
            if (v.size() != 1) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            if (v[0].type != token_type::INM) {
                throw std::invalid_argument("Invalid argument type");
            }

            _rf.pc = static_cast<std::uint32_t>(stoi((v[0].value)));

            return Token {std::to_string(_rf.pc), token_type::INM};
        }



    private:
        RegisterFile & _rf;
        Memory::text & _mem_t;

};

#endif