#ifndef READER_HPP
#define READER_HPP

#include <string>
#include <vector>
#include <iostream>


#include "ast.hpp"


class Reader {

    public:

        Reader(std::vector<Token> const & tokens) {
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

#endif