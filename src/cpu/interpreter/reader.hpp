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
            : _tokens{tokens}, _pos{0}, _current_token{_tokens[_pos]} {

            // print_tokens();
        }

        /**
        * Returns the token at the current position and increments the position.
        */
        Token next() {
            if (is_end()) throw std::out_of_range{"Reached end of inst"};

            Token token = _current_token;
            _current_token = _tokens[++_pos];

            // print_state();

            return token;
        }


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
            std::cout << "current_token: " << " [" << _pos <<  "] " << _current_token.string << '\n';
        }

        void print_tokens() const {
            /*
            Prints all tokens
            */

            std::cout << "tokens: ";
            for (const auto & i: _tokens)
                std::cout << i.string << ' ';
            std::cout << '\n';
        }

};

#endif