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

                v.push_back(Token {elem, token_type::NIL});
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

            /* Operators */
            if (_alu.repl_env.contains(token_str)) {
                type = token_type::OP;
            }
            /* Registers */
            else if (_rf.contains(token_str)) {
                type = token_type::REG;
            }
            /* Blocks */
            else if (token_str == "do") {
                type = token_type::BLK;
            }
            /* Conditionals */
            else if (token_str == "if") {
                type = token_type::CND;
            }
            /* Booleans */
            else if (token_str == "true" || token_str == "false") {
                type = token_type::BOOL;
            /* NIL */
            }
            else if (token_str == "nil") {
                type = token_type::NIL;
            }
            /* Numbers */
            else if (is_number(token_str)) {
                type = token_type::NUM;
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

                auto children = ast.get_children();

                // if the list is empty, return NIL
                if (children.size() == 0) {
                    return AST { Token {"nil", token_type::NIL} };
                }

                // if the list only has one non-list member, return the member
                if (children.size() == 1 && children[0].get_token().type != token_type::LIST) {
                    return AST_Node { children[0].get_token() };
                }

                std::vector<AST_Node> evaluated_list = eval_ast(ast).get_children();

                // get function (head)
                Token symbol = evaluated_list[0].get_token();

                switch (symbol.type) {
                    /* Blocks */
                    case  token_type::BLK: {
                        // evaluate the elements of the list and return the final evaluated element

                        Token result = symbol;
                        for (auto child : evaluated_list) {
                            result = eval_ast(child).get_token();
                        }

                        return AST_Node { result };
                    }

                    /* Conditionals */
                    case token_type::CND: {
                        // Evaluate the first parameter. If the result is anything other than nil or false, then evaluate the second parameter and return the result. Otherwise, evaluate the third parameter and return the result. If condition is false and there is no third parameter, then return nil

                        if (evaluated_list.size() > 4 || evaluated_list.size() < 3) {
                            throw LUISPDAException("Not enough arguments for 'if' statement");
                        }

                        Token first_param = eval_ast(evaluated_list[1]).get_token();

                        // if
                        if (first_param.type != token_type::NIL && first_param.value != "false") {
                            // then
                            return eval_ast(evaluated_list[2]);
                        }

                        if (evaluated_list.size() == 3) {  // no else
                            return AST_Node { Token {"nil", token_type::NIL} };
                        }

                        // else
                        return eval_ast(evaluated_list[3]);
                    }

                    /* Operators */
                    case token_type::OP: {
                        // call first item of the evaluated list as function using the rest of the evaluated list as its arguments

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

                            throw LUISPDAException(msg + " for operator '" + symbol.value + "'");
                        }
                    }

                    default:
                        throw LUISPDAException("Token " + symbol.value + " is not suitable as a symbol");
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
                case token_type::OP: {
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