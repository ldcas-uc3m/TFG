#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <ostream>



/* Token */

enum class token_type {
    LIST,  // list
    OP,  // operator
    NUM,  // number
    BOOL,  // bool
    NIL,  // undefined
    REG,  // register
    BLK,  // block statement
    CND,  // conditional statement
    EOI  // end of instruction
};

struct Token {
    std::string value;
    token_type type;
};



/* Abstract Syntax Tree */

class AST_Node final {

    public:
        AST_Node(Token token) : _token {token}, _children {} {}


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
        static std::ostream & print_tree(std::ostream & out, AST_Node const & ast, const std::string & prefix, bool last_child);
};

using AST = AST_Node;


#endif