#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>
#include <regex>

#include "register_file.hpp"
#include "reader.hpp"
#include "ast.hpp"
#include "../memory/text.hpp"
#include "../lib/string_manipulation.hpp"




/* Interpreter */

class Interpreter {
    /*
    LUISP-DA interpreter
    */

    public:
        Interpreter() { }

        void exec(const Memory::Instruction & inst) {
            /*
            Executes a LUISP-DA instruction
            */

            AST ast = read_inst(inst);
            std::cout << ast;

            // eval(ast);
        }

    private:
        // TODO: const refs 'n stuff

        /* READ - Lexer */
        AST read_inst(const Memory::Instruction & inst) {
            /*
            Reads a LUISP-DA instruction and generates its AST.
            */
            return read_str(inst);
        }

        std::vector<Token> tokenize(const std::string & string) {
            /*
            Takes a single string and return an array/list of all the tokens in it.
            */

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

        AST read_str(const std::string & string) {
            /*
            Creates a new Reader and calls read_token().
            */

           Reader reader { tokenize(string) };

           return read_token(reader);
        }

        AST_Node read_token(Reader & reader) {
            /*
            Reads a token, returns the tree asociated to that token.
            */
            if (reader.peek().string == "(") {
                return read_list(reader);
            }

            return read_atom(reader);
        }

        // TODO: optimize... use std::move for tokens?
        AST_Node read_list(Reader & reader) {
            AST_Node node { Token {reader.next().string, token_type::LIST} };

            while (reader.peek().string != ")") {
                if (reader.peek().type == token_type::EOI) {
                    std::cout << "found EOI" << std::endl;
                    throw;  // TODO: exception
                }
                node.add_child(read_token(reader));
            }

            if (!reader.is_end()) {
                reader.next();
            }

            return node;
        }

        AST_Node read_atom(Reader & reader) {
            std::string token_str = reader.next().string;
            token_type type;

            if (is_number(token_str)) {
                type = token_type::INM;
            }
            else if (token_str == "ADDI") {  // TODO: expand for all symbols
                type = token_type::SYM;

            }
            else {
                std::cout << "bad symbol: " << token_str << std::endl;
                throw;  // TODO: exception
            }

            return AST_Node { Token {token_str, type} };

        }


        /* EVAL */
        std::string eval(AST ast) {

        }

};


#endif