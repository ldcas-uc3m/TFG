#include "ast.hpp"

#include <string>
#include <vector>
#include <ostream>



std::ostream & AST_Node::print_tree(std::ostream & out, AST_Node const & ast, const std::string & prefix = "", bool last_child = false) {

    // print node
    out << prefix;
    out << (last_child ? "└──" : "├──");

    switch (ast._token.type) {
        case token_type::LIST:
            out << " [LIST]";
            break;
        case token_type::OP:
            out << " [OP] " << ast._token.value;
            break;
        case token_type::NUM:
            out << " [NUM] " << ast._token.value;
            break;
        case token_type::BOOL:
            out << " [BOOL] " << ast._token.value;
            break;
        case token_type::NIL:
            out << " [NIL] ";
            break;
        case token_type::REG:
            out << " [REG] " << ast._token.value;
            break;
        case token_type::BLK:
            out << " [BLK] " << ast._token.value;
            break;
        case token_type::CND:
            out << " [CND] " << ast._token.value;
            break;
        case token_type::CALL:
            out << " [CALL] " << ast._token.value;
            break;
        default:
            out << " [" << static_cast<int>(ast._token.type) << "] ";
            break;
    }
    out << '\n';

    // print children
    for (auto child = ast._children.begin(); child != ast._children.end(); ++child) {

        // check current child if last child
        bool is_last_child = (child + 1 == ast._children.end());

        // check parent node was the last child
        const std::string new_prefix = (last_child) ? "\t" : "│\t";

        print_tree(out, *child, prefix + new_prefix, is_last_child);
    }

    return out;
}