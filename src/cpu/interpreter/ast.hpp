#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <ostream>



/* Token */

enum class token_type {
    SYM,  // symbol
    INM,  // inmediate
    LIST,  // list
    REG,  // register
    EOI,  // end of instruction
    NS  // not set
};

struct Token {
    std::string value;
    token_type type;
};



/* Abstract Syntax Tree */

class AST_Node final {

    public:
        AST_Node(Token token) : _children {}, _token {token} {}


        /**
        * @brief Adds a child to the node
        */
        void add_child(AST_Node node) {
            _children.push_back(node);
        }


        /**
        * @brief Returns the token of the node
        */
        const Token get_token() const {
            return _token;
        }


        /**
        * @brief Returns a list of child nodes
        */
        const std::vector<AST_Node> get_children() const {
            return _children;
        }


        /* print node */
        friend std::ostream & operator << (std::ostream & out, AST_Node const & ast) {
            return print_tree(out, ast, "", true);
        }

    private:
        Token _token;
        std::vector<AST_Node> _children;


        /**
        * @brief Returns a ostream with a graphical representation of the specified node
        */
        static std::ostream & print_tree(std::ostream & out, AST_Node const & ast, const std::string & prefix = "", bool last_child = false) {

            // print node
            out << prefix;
            out << (last_child ? "└──" : "├──");

            switch (ast._token.type) {
                case token_type::LIST:
                    out << " [LIST]";
                    break;
                case token_type::INM:
                    out << " [INM] " << ast._token.value;
                    break;
                case token_type::SYM:
                    out << " [SYM] " << ast._token.value;
                    break;
                case token_type::REG:
                    out << " [REG] " << ast._token.value;
                    break;
                default:
                    out << " [" << static_cast<int>(ast._token.type) << "] " << ast._token.value;
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
};

using AST = AST_Node;


#endif