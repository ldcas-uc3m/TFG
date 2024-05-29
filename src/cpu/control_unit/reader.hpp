#ifndef READER_HPP
#define READER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <exception>

#include "ast.hpp"


class Reader final {

    public:

        Reader(std::vector<Token> && tokens)  // && moves (gets ownership)
            : _tokens{tokens}, _pos{0}, _current_token{_tokens[_pos]} {}


        /**
        * Returns the token at the current position and increments the position.
        */
        Token next();


        /**
        * Returns the token at the current position.
        */
        Token peek() const {
            return _current_token;
        }


        /**
        * Checks if it has reached the end of instrucions.
        */
        bool is_end() const {
            return static_cast<std::size_t>(_pos) + 1 == _tokens.size();
        }


    private:
        std::vector<Token> _tokens;
        int _pos;
        Token _current_token;

        /**
        * @brief Prints the state of the reader (current position and token)
        */
        void print_state();

        /**
        * @brief Prints all tokens
        */
        void print_tokens() const;

};

#endif