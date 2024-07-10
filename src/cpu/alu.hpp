#ifndef ALU_HPP
#define ALU_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <initializer_list>


#include "control_unit/ast.hpp"
#include "memory/text.hpp"
#include "memory/data.hpp"
#include "register_file.hpp"



using lisp_function = std::function<const Token (const std::vector<Token> &)>;
#define ALU_FUNCTION(func)  [this] (const std::vector<Token> & v) -> const Token { return this->func(v); }  // lambda wrapper for the functions


class ALU final {

    public:
        /* constructors */
        // TODO: single constructor that accepts init list and map
        ALU(
            std::initializer_list<std::pair<const std::string, std::string>> calls,
            RegisterFile & rf,
            Memory::text & mem_t,
            Memory::data & mem_d
        )
        :
            call_opcodes {calls},
            _rf {rf},
            _mem_t {mem_t},
            _mem_d {mem_d}
        {

            // check calls
            if (calls.size() != call_env.size())
                throw LUISPDAException("Invalid system calls list");

            for (const auto & [opcode, call_name] : call_opcodes) {
                if (!call_env.contains(call_name)) {
                    // FIXME: throwing this exception breaks things
                    throw LUISPDAException("Invalid system calls list");
                }
            }
        }

        ALU(
            std::unordered_map<std::string, std::string> calls,
            RegisterFile & rf,
            Memory::text & mem_t,
            Memory::data & mem_d
        )
        :
            call_opcodes {calls},
            _rf {rf},
            _mem_t {mem_t},
            _mem_d {mem_d}
        {

            // check calls
            if (calls.size() != call_env.size())
                throw LUISPDAException("Invalid system calls list");

            for (const auto & [opcode, call_name] : call_opcodes) {
                if (!call_env.contains(call_name)) {
                    // FIXME: throwing this exception breaks things
                    throw LUISPDAException("Invalid system calls list");
                }
            }
        }


        // map of operators names and function pointers
        const std::unordered_map<std::string, lisp_function> op_env {
            /* Integer operators */
            { "+", ALU_FUNCTION(add) },
            { "-", ALU_FUNCTION(sub) },
            { "*", ALU_FUNCTION(mul) },
            { "/", ALU_FUNCTION(div) },
            { "%", ALU_FUNCTION(_mod) },
            /* Boolean operators */
            { "<", ALU_FUNCTION(lt) },
            { ">", ALU_FUNCTION(gt) },
            { "<=", ALU_FUNCTION(let) },
            { ">=", ALU_FUNCTION(get) },
            { "==", ALU_FUNCTION(eq) },
            { "!=", ALU_FUNCTION(neq) },
            { "!", ALU_FUNCTION(neg) },
            /* MEM operators */
            { "mem", ALU_FUNCTION(get_mem) },
            { "mem!", ALU_FUNCTION(set_mem) },
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

        const Token _mod(const std::vector<Token> & v);


        /* BOOLEAN OPERATORS */

        const Token lt(const std::vector<Token> & v);

        const Token gt(const std::vector<Token> & v);

        const Token get(const std::vector<Token> & v);

        const Token let(const std::vector<Token> & v);

        const Token eq(const std::vector<Token> & v);

        const Token neq(const std::vector<Token> & v);

        const Token neg(const std::vector<Token> & v);


        /* REGISTER OPERATORS */

        const Token get_register(const std::vector<Token> & v);

        const Token set_register(const std::vector<Token> & v);


        /* MEM OPERATORS*/

        const Token get_mem(const std::vector<Token> & v);

        const Token set_mem(const std::vector<Token> & v);


        /* PROGRAM COUNTER OPERATORS*/

        const Token get_pc(const std::vector<Token> & v);

        const Token set_pc(const std::vector<Token> & v);


        /* SYSTEM CALLS */

        // map of call opcodes and call names
        const std::unordered_map<std::string, std::string> call_opcodes;


        // map of call names and functions
        const std::unordered_map<std::string, lisp_function> call_env {
            { "print_int", ALU_FUNCTION(print_int) },
            { "print_char", ALU_FUNCTION(print_char) },
            { "read_int", ALU_FUNCTION(read_int) },
            { "read_char", ALU_FUNCTION(read_char) },
            { "exit", ALU_FUNCTION(exit) }
        };

        const Token print_int(const std::vector<Token> & v);

        const Token print_char(const std::vector<Token> & v);

        const Token read_int(const std::vector<Token> & v);

        const Token read_char(const std::vector<Token> & v);

        const Token exit(const std::vector<Token> & v);


    private:
        RegisterFile & _rf;
        const Memory::text & _mem_t;
        Memory::data & _mem_d;


        /* AUX FUNCTIONS */

        bool _to_bool(const Token & token) const;

        Token _from_bool(bool value) const {
            return Token {value ? "true" : "false", token_type::BOOL};
        }


        int _to_num(const Token & token) const;

        Token _from_num(int num) const {
            return Token {std::to_string(num), token_type::NUM};
        }
};


#endif