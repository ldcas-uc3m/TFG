#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP



#include <string>
#include <vector>
#include <regex>

#include "register_file.hpp"
#include "reader.hpp"
#include "ast.hpp"
#include "alu.hpp"
#include "../memory/text.hpp"
#include "../lib/string_manipulation.hpp"






/* Interpreter */

class Interpreter {
    /*
    LUISP-DA interpreter
    */

    public:
        Interpreter(RegisterFile & rf) : _rf {rf} {
            _rf = rf;
        }

        /**
        * @brief Executes a LUISP-DA instruction
        */
        void exec(const Memory::Instruction & inst) {

            std::cout << "Instruction: " << inst << '\n';

            AST ast = read_inst(inst);
            std::cout << ast;

            AST result = eval(ast);

            std::cout << "Result: " << '\n' << result;
        }

    private:

        RegisterFile & _rf;


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
            if (reader.peek().string == "(") {
                return read_list(reader);
            }

            return read_atom(reader);
        }


        /**
        * @brief Reads a list token, returns the tree asociated to that token.
        */
        AST_Node read_list(Reader & reader) {

            // create token
            AST_Node node { Token {reader.next().string, token_type::LIST} };

            // read list
            while (reader.peek().string != ")") {

                if (reader.peek().type == token_type::EOI) {
                    std::cout << "EOI found before end of list token" << std::endl;
                    throw;  // TODO: exception
                }

                node.add_child(read_token(reader));
            }

            reader.next();

            return node;
        }


        /**
        * @brief Reads an atomic token, sets its type, adn returns the tree asociated to that token.
        */
        AST_Node read_atom(Reader & reader) {
            std::string token_str = reader.next().string;
            token_type type;

            /* Inmediates */
            if (is_number(token_str)) {
                type = token_type::INM;
            }
            /* Symbols */
            else if (repl_env.contains(token_str)) {
                type = token_type::SYM;
            }

            else {
                std::cout << "bad symbol: " << token_str << std::endl;
                throw;  // TODO: exception
            }

            return AST_Node { Token {token_str, type} };

        }



        /* EVAL */

        AST_Node eval(AST ast) {

            Token token = ast.get_token();

            if (token.type == token_type::LIST) {

                if (ast.get_children().size() == 0) {
                    return ast;
                }

                // call first item of the evaluated list as function using the rest of the evaluated list as its arguments
                std::vector<AST_Node> evaluated_list = eval_ast(ast).get_children();

                // get function (head)
                Token symbol = evaluated_list[0].get_token();
                lisp_function func = repl_env.find(symbol.string)->second;

                // get arguments (tail)
                std::vector<Token> args;

                for (auto it = evaluated_list.begin() + 1; it < evaluated_list.end(); ++it) {
                    args.push_back(it->get_token());
                }

                // function call
                return AST_Node { func(args) };

            }

            return eval_ast(ast);

        }


        AST_Node eval_ast(AST ast) {
            Token token = ast.get_token();

            switch (token.type) {
                case token_type::SYM: {
                    // check the symbol exists in REPL

                    if (!repl_env.contains(token.string))
                        throw;  // TODO: exception

                    return ast;
                }

                case token_type::LIST: {
                    // return a list with the result of calling EVAL on each of the members of the list

                    AST new_list {Token { "", token_type::LIST }};

                    for (auto child : ast.get_children()) {
                        new_list.add_child(eval(child));
                    }

                    return new_list;
                }

                default:
                    return ast;
            }
        }

};


#endif