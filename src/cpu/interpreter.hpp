#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>
#include <regex>

#include "register_file.hpp"
#include "../memory/text.hpp"
#include "../lib/string_manipulation.hpp"


// TODO: Separate in files under interpreter/

/* Token */

enum token_type {
    SYM,  // symbol
    INM,  // inmediate
    LIST,  // list
    EOI,  // end of instruction
    NS  // not set
};

struct Token {
    std::string string;
    token_type type;
};



/* Abstract Syntax Tree */

class AST_Node {

    public:
        AST_Node(Token token) : _children {} {
            _token = token;
        }

        void add_child(AST_Node node) {
            _children.push_back(node);
        }


        /* print node */
        friend std::ostream & operator << (std::ostream & out, AST_Node const & ast) {
            out << ast.print_tree(ast, "", true).rdbuf();

            return out;
        }

        static std::stringstream print_tree(AST_Node const & ast, const std::string & prefix = "", bool last_child = false) {
            /*
            Returns a stringstream with a graphical representation of the specified node
            */

            std::stringstream sout;

            // print node
            sout << prefix;
            sout << (last_child ? "└──" : "├──");

            // TODO: is there a better way to do this???
            switch (ast._token.type) {
                case LIST:
                    sout << " [LIST]";
                    break;
                case INM:
                    sout << " [INM] " << ast._token.string;
                    break;
                case SYM:
                    sout << " [SYM] " << ast._token.string;
                    break;
                default:
                    sout << " [" << ast._token.type << "] " << ast._token.string;
                    break;
            }
            sout << std::endl;

            // print children
            for (const auto & child : ast._children) {

                // check current child if last child
                bool is_last_child;
                (&child == &ast._children.back()) ? is_last_child = true : is_last_child = false;

                // check parent node was the last child
                const std::string new_prefix = (last_child) ? "\t" : "│\t";

                sout << print_tree(child, prefix + new_prefix, is_last_child).rdbuf();
            }

            return sout;

        }

    private:
        Token _token;
        std::vector<AST_Node> _children;

};

typedef AST_Node AST;



/* Reader */

class Reader {

    public:

        Reader(std::vector<Token> tokens) {
            _tokens = tokens;
            _pos = 0;
            _current_token = _tokens[_pos];

            print_tokens();
        }

        Token next() {
            /*
            Returns the token at the current position and increments the position.
            */
            if (is_end()) {
                std::cout << "Reached end of inst" << std::endl;
                throw;  // TODO: Exception
            }

            Token token = _current_token;
            _current_token = _tokens[++_pos];

            // print_state();

            return token;
        }

        Token peek() {
            /*
            Returns the token at the current position.
            */

            return _current_token;
        }

        bool is_end() {
            return _pos == _tokens.size() - 1;
        }

    private:
        std::vector<Token> _tokens;
        int _pos;
        Token _current_token;

        void print_state() {
            /*
            Prints the state of the reader (current position and token)
            */

            std::cout << "pos: " << _pos << '\t';
            std::cout << "current_token: " << " [" << _pos <<  "] " << _current_token.string << std::endl;
        }

        void print_tokens() {
            /*
            Prints all tokens
            */

            std::cout << "tokens: ";
            for (const auto & i: _tokens)
                std::cout << i.string << ' ';
            std::cout << std::endl;
        }

};



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
            std::cout << ast.print_tree(ast, "", true).rdbuf();

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

                v.push_back(Token {elem, NS});
            }

            v.push_back(Token {"", EOI});  // add end of instruction

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
            AST_Node node { Token {reader.next().string, LIST} };

            while (reader.peek().string != ")") {
                if (reader.peek().type == EOI) {
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
                type = INM;
            }
            else if (token_str == "ADDI") {  // TODO: expand for all symbols
                type = SYM;

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