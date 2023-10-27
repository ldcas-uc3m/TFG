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

            AST ast = read_inst(inst);
            std::cout << ast;

            // eval(ast);
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

        AST_Node read_token(Reader & reader) {
            /*
            Reads a token, returns the tree asociated to that token.
            */
            if (reader.peek().string == "(") {
                return read_list(reader);
            }

            return read_atom(reader);
        }

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
            // std::map<std::string, lisp_function> repl_env;

            // repl_env.emplace("ADDI", addi);
            // repl_env.emplace("ADDI", [] (Token t) -> Token {return jflkjkd});

        }

};

using lisp_function = std::function<Token (*) (std::vector<Token>)>;

#endif