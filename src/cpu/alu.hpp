#ifndef ALU_HPP
#define ALU_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

#include "interpreter/ast.hpp"
#include "memory/text.hpp"
#include "register_file.hpp"



using lisp_function = std::function<const Token (const std::vector<Token> &)>;


class ALU final {

    public:
        ALU(RegisterFile & rf, Memory::text & mem_t) : _rf {rf}, _mem_t {mem_t} {}

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

        const Token add(const std::vector<Token> & v);

        const Token sub(const std::vector<Token> & v);

        const Token mul(const std::vector<Token> & v);

        const Token div(const std::vector<Token> & v);

        const Token mod(const std::vector<Token> & v);


        /* BOOLEAN OPERATORS */

        const Token gt(const std::vector<Token> & v);

        const Token lt(const std::vector<Token> & v);

        const Token get(const std::vector<Token> & v);

        const Token let(const std::vector<Token> & v);

        const Token eq(const std::vector<Token> & v);

        const Token neq(const std::vector<Token> & v);

        const Token neg(const std::vector<Token> & v);


        /* REGISTER OPERATORS */

        const Token get_register (const std::vector<Token> & v);

        const Token set_register (const std::vector<Token> & v);


        /* PROGRAM COUNTER OPERATORS*/

        const Token get_pc (const std::vector<Token> & v);

        const Token set_pc (const std::vector<Token> & v);



    private:
        RegisterFile & _rf;
        const Memory::text & _mem_t;

        bool to_bool(const Token & token) const;

        Token from_bool(bool value) const {
            return Token {std::to_string(value), token_type::BOOL};
        }


        int to_num(const Token & token) const;

        Token from_num(int num) const {
            return Token {std::to_string(num), token_type::NUM};
        }
};


#endif