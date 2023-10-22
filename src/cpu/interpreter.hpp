#include <string>
#include <vector>

#include "register_file.hpp"
#include "../memory/text.cpp"
#include "../lib/string_manipulation.hpp"




enum token_type {
    SYM,  // symbol
    INM,  // inmediate
    LIST  // list
};

struct Token {
    std::string string;
    token_type type;
};



class AST_Node {

    public:
        AST_Node(Token token) : _children {} {
            _token = token;
        }

        void add_child(AST_Node node) {
            _children.push_back(node);
        }

    private:
        Token _token;
        std::vector<AST_Node> _children;
};

typedef AST_Node AST;



class Reader {

    public:

        Reader(std::vector<std::string> tokens) {
            _tokens = tokens;
            _pos = 0;
            _current_token = _tokens[_pos];
        }

        std::string next() {
            /*
            Returns the token at the current position and increments the position.
            */
            std::string token = _current_token;
            _current_token = _tokens[++_pos];

            return token;
        }

        std::string peek() {
            /*
            Returns the token at the current position.
            */

            return _current_token;
        }

    private:
        std::vector<std::string> _tokens;
        int _pos;
        std::string _current_token;

};



class Interpreter {
    /*
    LUISP-DA interpreter
    */

    public:
        Interpreter() { }

        void exec(const Instruction & inst) {
            /*
            Executes a LUISP-DA instruction
            */

            read(inst);
            // eval();

        }

    private:

        /* READ - Lexer*/
        std::string read(const Instruction & inst) {
            read_str(inst.get_instuction());
        }

        std::vector<std::string> tokenize(const std::string & string) {
            /*
            Takes a single string and return an array/list of all the tokens in it.
            */

            std::vector<std::string> v;
            split_string(string, v, ' ');

            return v;
        }

        AST read_str(const std::string & string) {
            /*
            Creates a new Reader and calls read_form().
            */

           Reader reader { tokenize(string) };

           return read_form(reader);
        }

        AST_Node read_form(Reader & reader) {
            if (reader.peek() == "(") {
                return read_list(reader);
            }
            else {
                return read_atom(reader);
            }
        }

        AST_Node read_list(Reader & reader) {
            AST_Node node { Token {reader.next(), LIST} };
            node.add_child(read_form(reader));

            return node;
        }

        AST_Node read_atom(Reader & reader) {
            std::string token_str = reader.next();
            token_type type;

            if (is_number(token_str)) {
                type = INM;
            }
            else if (token_str == "ADDI") {  // TODO: expand for all symbols
                type = SYM;

            }
            else {
                // TODO: exception
                throw;
            }

            return AST_Node { Token {token_str, type} };

        }



        /* EVAL */
        std::string eval(std::string inst) {

        }

};