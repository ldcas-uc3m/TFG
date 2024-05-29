#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP



#include <string>
#include <vector>
#include <unordered_map>


#include "register_file.hpp"
#include "reader.hpp"
#include "ast.hpp"
#include "cpu/alu.hpp"
#include "memory/text.hpp"
#include "memory/data.hpp"



/* LUISP-DA control_unit, based on Make A Lisp */

class Interpreter final {

    public:
        /* constructors */
        // TODO: single constructor that accepts init list and map
        Interpreter(
            RegisterFile & rf,
            Memory::text & mem_t,
            Memory::data & mem_d,
            std::initializer_list<std::pair<const std::string, std::string>> calls
        )
        :
            _rf {rf},
            _mem_t {mem_t},
            _mem_d {mem_d},
            _alu {calls, rf, mem_t, mem_d}
        { }

        Interpreter(
            RegisterFile & rf,
            Memory::text & mem_t,
            Memory::data & mem_d,
            std::unordered_map<std::string, std::string> calls
        )
        :
            _rf {rf},
            _mem_t {mem_t},
            _mem_d {mem_d},
            _alu {calls, rf, mem_t, mem_d}
        { }


        /**
        * @brief Executes the next LUISP-DA instruction
        * @return True if there are more instructions to execute, False otherwise.
        */
        bool next();


        /**
        * @brief Executes a LUISP-DA instruction
        */
        AST_Node exec(const Memory::Instruction & inst);


    private:

        RegisterFile & _rf;
        const Memory::text & _mem_t;
        Memory::data & _mem_d;
        ALU _alu;


        /* READ - Lexer */

        /**
        * @brief Reads a LUISP-DA instruction and generates its AST.
        */
        AST read_inst(const Memory::Instruction & inst) {
            return read_str(inst);
        }


        /**
        * @brief Takes a single string and return an array/list of all the tokens in it.
        */
        std::vector<Token> tokenize(const std::string & string);


        /**
        * @brief Creates a new Reader and calls read_token().
        */
        AST read_str(const std::string & string) {

           Reader reader { tokenize(string) };

           return read_token(reader);
        }


        /**
        * @brief Lexer. Reads a token, checks if it's the start of a list, and calls the appropiate function to read the token(s). Returns the tree associated to that token.
        */
        AST_Node read_token(Reader & reader) {
            if (reader.peek().value == "(") {
                return read_list(reader);
            }

            return read_atom(reader);
        }


        /**
        * @brief Reads a list token, returns the node asociated to that token.
        */
        AST_Node read_list(Reader & reader);


        /**
        * @brief Sets an atomic token's type, and returns the node asociated to that token.
        */
        AST_Node read_atom(Reader & reader);



        /* EVAL */

        const AST_Node eval(const AST & ast) const {
            return eval_token(ast);
        }

        /**
        * @brief Evaluates an AST and executes the specified function.
        */
        const AST_Node eval_token(const AST & ast) const;


        /**
        * @brief Recursively evaluates an AST node depending on its token type.
        */
        const AST_Node eval_ast(const AST & ast) const;

};



#endif