#include "control_unit.hpp"

#include <string>
#include <vector>
#include <regex>
#include <format>
#include <stdexcept>

#include "reader.hpp"
#include "ast.hpp"
#include "cpu/register_file.hpp"
#include "cpu/alu.hpp"
#include "memory/text.hpp"
#include "lib/string_manipulation.hpp"
#include "exceptions/exceptions.hpp"



bool Interpreter::next() {
    /* fetch */
    Memory::Instruction inst = _mem_t.get_instuction(_rf.pc);
    _rf.pc += Memory::WORD_SIZE;

    /* decode */
    AST ast = read_inst(inst);

    /* execute */
    eval(ast);

    return _rf.pc < _mem_t.get_last_address();
}


AST_Node Interpreter::exec(const Memory::Instruction & inst) {
    /* decode */
    std::cout << "Instruction: " << inst << '\n';

    AST ast = read_inst(inst);
    std::cout << ast;

    /* execute */
    AST_Node result = eval(ast);

    std::cout << "Result: " << '\n' << result << '\n';

    return result;
}


std::vector<Token> Interpreter::tokenize(const std::string & string) {

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


AST_Node Interpreter::read_atom(Reader & reader) {  // lexer
    std::string token_str = reader.next().value;
    token_type type;

    /* Operators */
    if (_alu.op_env.contains(token_str)) {
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
    /* System call */
    else if (token_str == "call") {
        type = token_type::CALL;
    }
    /* Numbers */
    else if (is_number(token_str)) {
        type = token_type::NUM;
    }
    else if (token_str.substr(0, 2) == "0x" && token_str.length() == 10) {  // hex format
        type = token_type::NUM;
        std::uint32_t value = std::stoul(token_str, nullptr, 16);  // convert to regular uint
        token_str = std::to_string(value);
    }

    else {
        throw LUISPDAException("Unrecognized type for token: " + token_str);
    }

    return AST_Node { Token {token_str, type} };

}


AST_Node Interpreter::read_list(Reader & reader) {

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


const AST_Node Interpreter::eval_token(const AST & ast) const {

    Token token = ast.get_token();

    if (token.type == token_type::LIST) {

        auto children = ast.get_children();

        // if the list is empty, return NIL
        if (children.size() == 0) {
            return AST { Token {"nil", token_type::NIL} };
        }

        // if the list only has one non-list, non-op member, return the member
        if (children.size() == 1 && children[0].get_token().type != token_type::LIST && children[0].get_token().type != token_type::OP) {
            return AST_Node { children[0].get_token() };
        }

        // get function (head)
        Token symbol = children[0].get_token();

        switch (symbol.type) {
            /* Blocks */
            case  token_type::BLK: {
                // evaluate the elements of the list and return the final evaluated element

                Token result = symbol;
                for (auto child : children) {
                    result = eval_token(child).get_token();
                }

                return AST_Node { result };
            }

            /* Conditionals */
            case token_type::CND: {
                // Evaluate the first parameter. If the result is anything other than nil or false, then evaluate the second parameter and return the result. Otherwise, evaluate the third parameter and return the result. If condition is false and there is no third parameter, then return nil

                if (children.size() > 4 || children.size() < 3) {
                    throw LUISPDAException("Incorrect number of arguments for 'if' statement");
                }

                Token first_param = eval_token(children[1]).get_token();

                // if
                if (first_param.type != token_type::NIL && first_param.value != "false") {
                    // then
                    return eval_token(children[2]);
                }

                if (children.size() == 3) {  // no else
                    return AST_Node { Token {"nil", token_type::NIL} };
                }

                // else
                return eval_token(children[3]);
            }

            /* Operators */
            case token_type::OP: {
                // call first item of the evaluated list as function using the rest of the evaluated list as its arguments

                std::vector<AST_Node> evaluated_list = eval_ast(ast).get_children();

                lisp_function func = _alu.op_env.find(symbol.value)->second;

                // get arguments (tail)
                std::vector<Token> args;
                for (auto it = evaluated_list.begin() + 1; it < evaluated_list.end(); ++it) {
                    args.push_back(it->get_token());
                }

                // function call
                try {
                    return AST_Node { func(args) };
                }
                catch (std::invalid_argument &e) {
                    std::string msg = e.what();

                    throw LUISPDAException(msg + " for operator '" + symbol.value + "'");
                }
            }
            /* System calls */
            case token_type::CALL: {
                // find the correct system call to execute acording to its opcode and execute it

                std::vector<AST_Node> evaluated_list = eval_ast(ast).get_children();

                // get opcode (head)
                Token opcode = evaluated_list[1].get_token();

                // get arguments (tail)
                std::vector<Token> args;
                for (auto it = evaluated_list.begin() + 2; it < evaluated_list.end(); ++it) {
                    args.push_back(it->get_token());
                }

                if (!_alu.call_opcodes.contains(opcode.value))  // check opcode
                    throw LUISPDAException(std::format("Invalid opcode '{}'", opcode.value));

                // check call name
                std::string call = _alu.call_opcodes.find(opcode.value)->second;
                if (!_alu.call_env.contains(call))
                    throw LUISPDAException(std::format("Invalid call name '{}'", call));

                // function call
                lisp_function func = _alu.call_env.find(call)->second;

                try {
                    return AST_Node { func(args) };
                }
                catch (std::invalid_argument &e) {
                    std::string msg = e.what();

                    throw LUISPDAException(msg + " for operator '" + symbol.value + "'");
                }
            }

            default:
                throw LUISPDAException("Token '" + symbol.value + "' is not suitable as a symbol");
        }
    }

    return eval_ast(ast);
}


const AST_Node Interpreter::eval_ast(const AST & ast) const {
    Token token = ast.get_token();

    switch (token.type) {
        case token_type::OP: {
            // check the symbol exists in REPL

            if (!_alu.op_env.contains(token.value))
                throw LUISPDAException("Unrecognized operator '" + token.value + "'");


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