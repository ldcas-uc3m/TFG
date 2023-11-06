#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP



#include <string>
#include <vector>
#include <regex>
#include <format>
#include <stdexcept>


#include "../register_file.hpp"
#include "reader.hpp"
#include "ast.hpp"
#include "../register_file.hpp"
#include "../alu.hpp"
#include "../../memory/text.hpp"
#include "../../lib/string_manipulation.hpp"
#include "../../exceptions.hpp"





/* LUISP-DA interpreter */

class Interpreter {

    public:
        Interpreter(RegisterFile & rf, Memory::text & mem) : _rf {rf}, _mem {mem}, _alu {rf, mem} { }

        /**
        * @brief Executes the next LUISP-DA instruction
        */
        void next() {
            // TODO: signal end of instructions

            /* fetch */
            Memory::Instruction inst = _mem.get_instuction(_rf.pc);
            _rf.pc += Memory::WORD_SIZE;

            /* decode */
            AST ast = read_inst(inst);

            /* execute */
            eval(ast);
        }


        /**
        * @brief Executes a LUISP-DA instruction
        */
        AST_Node exec(const Memory::Instruction & inst) {
            /* decode */
            std::cout << "Instruction: " << inst << '\n';

            AST ast = read_inst(inst);
            std::cout << ast;

            /* execute */
            AST_Node result = eval(ast);

            std::cout << "Result: " << '\n' << result << '\n';

            return result;
        }


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
        std::vector<Token> tokenize(const std::string & string) {

            const std::regex re {R"((?:\s,)*([\[\]()]|"(?:\\.|[^\\"])*"?|[^\s\[\]{}()'"`,;]*))"};
            std::vector<Token> v;

            std::sregex_iterator start {string.cbegin(), string.cend(), re};
            std::sregex_iterator end;

            for (auto i = start; i != end; ++i) {
                std::string elem = i->str();

                if (elem == "") continue;

                v.push_back(Token {elem, token_type::NS});
            }

            v.push_back(Token {"", token_type::EOI});  // add end of instruction

            return v;
        }


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
        AST_Node read_list(Reader & reader) {

            // create token
            AST_Node node { Token {reader.next().value, token_type::LIST} };

            // read list
            while (reader.peek().value != ")") {

                if (reader.peek().type == token_type::EOI) {
                    throw LUISPDAException("EOI found before end of list token ')'");
                }

                node.add_child(read_token(reader));
            }

            reader.next();

            return node;
        }


        /**
        * @brief Sets an atomic token's type, and returns the node asociated to that token.
        */
        AST_Node read_atom(Reader & reader) {
            std::string token_str = reader.next().value;
            token_type type;

            /* Symbols */
            if (_alu.repl_env.contains(token_str)) {
                type = token_type::SYM;
            }
            else if (token_str == "begin") {
                type = token_type::BEG;
            }
            /* Registers */
            else if (_rf.contains(token_str)) {
                type = token_type::REG;
            }
            /* Inmediates */
            else if (is_number(token_str)) {
                type = token_type::INM;
            }

            else {
                throw LUISPDAException("Unrecognized type for token: " + token_str);
            }

            return AST_Node { Token {token_str, type} };

        }



        /* EVAL */

        const AST_Node eval(const AST & ast) const {
            return eval_token(ast);
        }

        /**
        * @brief Evaluates an AST and executes the specified function.
        */
        const AST_Node eval_token(const AST & ast) const {

            Token token = ast.get_token();

            if (token.type == token_type::LIST) {

                if (ast.get_children().size() == 0) {
                    return ast;
                }

                // call first item of the evaluated list as function using the rest of the evaluated list as its arguments
                std::vector<AST_Node> evaluated_list = eval_ast(ast).get_children();

                // get function (head)
                Token symbol = evaluated_list[0].get_token();

                if (symbol.type == token_type::BEG) {
                    for (auto child : evaluated_list) {
                        eval_ast(child);

                        return AST_Node { Token {"begin", token_type::BEG} };
                    }
                }

                lisp_function func = _alu.repl_env.find(symbol.value)->second;

                // get arguments (tail)
                std::vector<Token> args;

                for (auto it = evaluated_list.begin() + 1; it < evaluated_list.end(); ++it) {
                    args.push_back(it->get_token());
                }

                // function call
                try {
                    return AST_Node { func(args) };
                }
                catch (std::invalid_argument e) {
                    std::string msg = e.what();

                    throw LUISPDAException(msg + " for operator '" + symbol.value + "'" );
                }

            }

            return eval_ast(ast);

        }


        /**
        * @brief Recursively evaluates an AST node depending on its token type.
        */
        const AST_Node eval_ast(const AST & ast) const {
            Token token = ast.get_token();

            switch (token.type) {
                case token_type::SYM: {
                    // check the symbol exists in REPL

                    if (!_alu.repl_env.contains(token.value))
                        throw LUISPDAException("Unrecognized symbol: " + token.value);


                    return ast;
                }

                case token_type::LIST: {
                    // return a list with the result of calling EVAL on each of the members of the list

                    AST new_list {Token { "", token_type::LIST }};

                    for (auto child : ast.get_children()) {
                        new_list.add_child(eval_token(child));
                    }

                    return new_list;
                }

                default:
                    return ast;
            }
        }

};



#endif