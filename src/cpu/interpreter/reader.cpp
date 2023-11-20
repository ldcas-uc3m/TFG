#include "reader.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <exception>

#include "ast.hpp"



Token Reader::next() {
    if (is_end()) throw std::out_of_range{"Reached end of instruction"};

    Token token = _current_token;
    _current_token = _tokens[++_pos];

    return token;
}


void Reader::print_state() {

    std::cout << "pos: " << _pos << '\t';
    std::cout << "current_token: " << " [" << _pos <<  "] " << _current_token.value << '\n';
}

void Reader::print_tokens() const {
    /*
    Prints all tokens
    */

    std::cout << "tokens: ";
    for (const auto & i: _tokens)
        std::cout << i.value << ' ';
    std::cout << '\n';
}