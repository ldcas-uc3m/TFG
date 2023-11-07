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
            /* Integer operators */
            { "+", ALU_FUNCTION(add) },
            { "-", ALU_FUNCTION(sub) },
            { "*", ALU_FUNCTION(mul) },
            { "/", ALU_FUNCTION(div) },
            { "%", ALU_FUNCTION(mod) },
            /* Boolean operators */
            { "<", ALU_FUNCTION(lt) },
            { ">", ALU_FUNCTION(gt) },
            { "<=", ALU_FUNCTION(let) },
            { ">=", ALU_FUNCTION(get) },
            { "==", ALU_FUNCTION(eq) },
            { "!=", ALU_FUNCTION(neq) },
            { "!", ALU_FUNCTION(neg) },
            /* Register operators */
            { "reg", ALU_FUNCTION(get_register) },
            { "reg!", ALU_FUNCTION(set_register) },
            /* PC operators */
            { "pc", ALU_FUNCTION(get_pc) },
            { "pc!", ALU_FUNCTION(set_pc) }
        };


        /* INTEGER OPERATORS */

        // TODO: macro/template this shit?

        const Token add(const std::vector<Token> & v) {
            // check parameters
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            int result = to_num(v[0]) + to_num(v[1]);

            return from_num(result);
        }

        const Token sub(const std::vector<Token> & v) {
            if (v.size() == 2) {
                int result = to_num(v[0]) - to_num(v[1]);
                return from_num(result);
            }
            else if (v.size() == 1) {
                int result = - to_num(v[0]);
                return from_num(result);
            }
            else
                throw std::invalid_argument("Incorrect number of parameters");


        }

        const Token mul(const std::vector<Token> & v) {
            // check parameters
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            int result = to_num(v[0]) * to_num(v[1]);

            return from_num(result);
        }

        const Token div(const std::vector<Token> & v) {
            // check parameters
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            int result = to_num(v[0]) / to_num(v[1]);

            return from_num(result);
        }

        const Token mod(const std::vector<Token> & v) {
            // check parameters
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            int result = to_num(v[0]) % to_num(v[1]);

            return from_num(result);
        }


        /* BOOLEAN OPERATORS */

        const Token gt(const std::vector<Token> & v) {
            // check parameters
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            bool result = to_num(v[0]) > to_num(v[1]);

            return from_bool(result);
        }

        const Token lt(const std::vector<Token> & v) {
            // check parameters
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            bool result = to_num(v[0]) < to_num(v[1]);

            return from_bool(result);
        }

        const Token get(const std::vector<Token> & v) {
            // check parameters
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            bool result = to_num(v[0]) >= to_num(v[1]);

            return from_bool(result);
        }

        const Token let(const std::vector<Token> & v) {
            // check parameters
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            bool result = to_num(v[0]) <= to_num(v[1]);

            return from_bool(result);
        }

        const Token eq(const std::vector<Token> & v) {
            // check parameters
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            bool result = to_num(v[0]) == to_num(v[1]);

            return from_bool(result);
        }

        const Token neq(const std::vector<Token> & v) {
            // check parameters
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            bool result = to_num(v[0]) != to_num(v[1]);

            return from_bool(result);
        }

        const Token neg(const std::vector<Token> & v) {
            // check parameters
            if (v.size() != 1) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            bool result = !to_bool(v[0]);

            return from_bool(result);
        }


        /* REGISTER OPERATORS */

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

            return Token {std::to_string(result), token_type::NUM};
        }


        const Token set_register (const std::vector<Token> & v) {
            if (v.size() != 2) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            if (v[0].type != token_type::REG || v[1].type != token_type::NUM) {
                throw std::invalid_argument("Invalid argument type");
            }

            std::uint32_t value = static_cast<std::uint32_t>(stoi(v[1].value));
            _rf[v[0].value] = value;

            return Token {std::to_string(value), token_type::NUM};
        }


        /* PROGRAM COUNTER OPERATORS*/

        const Token get_pc (const std::vector<Token> & v) {
            if (v.size() != 0) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            return Token {std::to_string(_rf.pc), token_type::NUM};
        }

        const Token set_pc (const std::vector<Token> & v) {
            if (v.size() != 1) {
                throw std::invalid_argument("Incorrect number of parameters");
            }

            if (v[0].type != token_type::NUM) {
                throw std::invalid_argument("Invalid argument type");
            }

            _rf.pc = static_cast<std::uint32_t>(stoi((v[0].value)));

            return Token {std::to_string(_rf.pc), token_type::NUM};
        }



    private:
        RegisterFile & _rf;
        Memory::text & _mem_t;

        bool to_bool(const Token & token) const {
            if (token.type != token_type::BOOL) {
                throw std::invalid_argument("Invalid argument type(s)");
            }

            if (token.value == "true")
                return true;
            else if (token.value == "false")
                return false;
            else
                throw std::invalid_argument("Invalid BOOL token value '" + token.value + "'");
        }

        Token from_bool(bool value) const {
            return Token {std::to_string(value), token_type::BOOL};
        }


        int to_num(const Token & token) const {
            if (token.type != token_type::NUM) {
                throw std::invalid_argument("Invalid argument type(s)");
            }

            return stoi(token.value);
        }

        Token from_num(int num) const {
            return Token {std::to_string(num), token_type::NUM};
        }
};


#endif