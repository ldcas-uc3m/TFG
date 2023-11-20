#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP



#include <string>
#include <vector>


#include "register_file.hpp"
#include "reader.hpp"
#include "ast.hpp"
#include "cpu/alu.hpp"
#include "memory/text.hpp"



/* LUISP-DA interpreter */

class Interpreter final {

    public:
        Interpreter(RegisterFile & rf, Memory::text & mem) : _rf {rf}, _mem {mem}, _alu {rf, mem} { }

        /**
        * @brief Executes the next LUISP-DA instruction
        */
        void next();


        /**
        * @brief Executes a LUISP-DA instruction
        */
        AST_Node exec(const Memory::Instruction & inst);


    private:

        RegisterFile & _rf;
        Memory::text & _mem;
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
        * @brief Reads a token, checks if it's the start of a list, and calls the appropiate function to read the token(s). Returns the tree associated to that token.
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