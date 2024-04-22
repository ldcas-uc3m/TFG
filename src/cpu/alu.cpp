#include "alu.hpp"

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>
#include <stdexcept>

#include "interpreter/ast.hpp"
#include "exceptions.hpp"
#include "memory/text.hpp"
#include "register_file.hpp"



/* INTEGER OPERATORS */

const Token ALU::add(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2)
        throw std::invalid_argument("Incorrect number of parameters");

    int result = _to_num(v[0]) + _to_num(v[1]);

    return _from_num(result);
}


const Token ALU::sub(const std::vector<Token> & v) {
    if (v.size() == 2) {
        int result = _to_num(v[0]) - _to_num(v[1]);
        return _from_num(result);
    }
    else if (v.size() == 1) {
        int result = - _to_num(v[0]);
        return _from_num(result);
    }
    else
        throw std::invalid_argument("Incorrect number of parameters");
}


const Token ALU::mul(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2)
        throw std::invalid_argument("Incorrect number of parameters");

    int result = _to_num(v[0]) * _to_num(v[1]);

    return _from_num(result);
}


const Token ALU::div(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2)
        throw std::invalid_argument("Incorrect number of parameters");

    int result = _to_num(v[0]) / _to_num(v[1]);

    return _from_num(result);
}


const Token ALU::_mod(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2)
        throw std::invalid_argument("Incorrect number of parameters");

    int result = _to_num(v[0]) % _to_num(v[1]);

    return _from_num(result);
}



/* BOOLEAN OPERATORS */

const Token ALU::gt(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2)
        throw std::invalid_argument("Incorrect number of parameters");

    bool result = _to_num(v[0]) > _to_num(v[1]);

    return _from_bool(result);
}


const Token ALU::lt(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2)
        throw std::invalid_argument("Incorrect number of parameters");

    bool result = _to_num(v[0]) < _to_num(v[1]);

    return _from_bool(result);
}


const Token ALU::get(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2)
        throw std::invalid_argument("Incorrect number of parameters");

    bool result = _to_num(v[0]) >= _to_num(v[1]);

    return _from_bool(result);
}


const Token ALU::let(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2)
        throw std::invalid_argument("Incorrect number of parameters");

    bool result = _to_num(v[0]) <= _to_num(v[1]);

    return _from_bool(result);
}


const Token ALU::eq(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2)
        throw std::invalid_argument("Incorrect number of parameters");

    bool result = _to_num(v[0]) == _to_num(v[1]);

    return _from_bool(result);
}


const Token ALU::neq(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2)
        throw std::invalid_argument("Incorrect number of parameters");

    bool result = _to_num(v[0]) != _to_num(v[1]);

    return _from_bool(result);
}


const Token ALU::neg(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 1)
        throw std::invalid_argument("Incorrect number of parameters");

    bool result = !_to_bool(v[0]);

    return _from_bool(result);
}



/* REGISTER OPERATORS */

const Token ALU::get_register(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 1)
        throw std::invalid_argument("Incorrect number of parameters");

    if (v[0].type != token_type::REG)
        throw std::invalid_argument("Invalid argument type");

    // get value
    std::uint32_t result;
    try {
        result = _rf[v[0].value];
    }
    catch (std::out_of_range &e) {
        throw LUISPDAException("Register " + v[0].value + " not found.");
    }

    return Token {std::to_string(result), token_type::NUM};
}


const Token ALU::set_register(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2)
        throw std::invalid_argument("Incorrect number of parameters");

    if (v[0].type != token_type::REG)
        throw std::invalid_argument("Invalid argument type");
    if (v[1].type != token_type::NUM)
        throw std::invalid_argument("Invalid argument type");


    std::uint32_t value = static_cast<std::uint32_t>(_to_num(v[1]));
    _rf[v[0].value] = value;

    return Token {std::to_string(value), token_type::NUM};
}



/* MEM OPERATORS*/

const Token ALU::get_mem(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 1)
        throw std::invalid_argument("Incorrect number of parameters");

    if (v[0].type != token_type::NUM)
        throw std::invalid_argument("Invalid argument type");

    // get value
    std::uint32_t result = _mem_d.get_value(static_cast<Memory::Address>(_to_num(v[0])));

    return Token {std::to_string(result), token_type::NUM};
}


const Token ALU::set_mem(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2)
        throw std::invalid_argument("Incorrect number of parameters");

    if (v[0].type != token_type::NUM)
        throw std::invalid_argument("Invalid argument type");
    if (v[1].type != token_type::NUM)
        throw std::invalid_argument("Invalid argument type");

    std::uint32_t addr = static_cast<std::uint32_t>(_to_num(v[0]));
    std::uint32_t value = static_cast<std::uint32_t>(_to_num(v[1]));

    _mem_d.set_value(addr, value);

    return Token {std::to_string(value), token_type::NUM};
}



/* PROGRAM COUNTER OPERATORS*/

const Token ALU::get_pc(const std::vector<Token> & v) {
    if (v.size() != 0)
        throw std::invalid_argument("Incorrect number of parameters");

    return Token {std::to_string(_rf.pc), token_type::NUM};
}

const Token ALU::set_pc(const std::vector<Token> & v) {
    if (v.size() != 1)
        throw std::invalid_argument("Incorrect number of parameters");


    _rf.pc = static_cast<std::uint32_t>(_to_num(v[0]));

    return Token {std::to_string(_rf.pc), token_type::NUM};
}



/* SYSTEM CALLS */

const Token ALU::print_int(const std::vector<Token> & v) {
    if (v.size() != 1)
        throw std::invalid_argument("Incorrect number of parameters");

    // TODO: print from register??
    // if (v[0].type != token_type::REG)
    //     throw std::invalid_argument("Invalid argument type");

    // // get value
    // std::uint32_t result;
    // try {
    //     result = _rf[v[0].value];
    // }
    // catch (std::out_of_range &e) {
    //     throw LUISPDAException("Register " + v[0].value + " not found.");
    // }

    // std::cout << result;
    std::cout << std::to_string(_to_num(v[0])) << std::flush;

    return Token {"nil", token_type::NIL};
}

const Token ALU::print_char(const std::vector<Token> & v) {
    if (v.size() != 1)
        throw std::invalid_argument("Incorrect number of parameters");

    std::cout << static_cast<char>(_to_num(v[0])) << std::flush;

    return Token {"nil", token_type::NIL};
}

const Token ALU::read_int(const std::vector<Token> & v) {
    if (v.size() != 1)
        throw std::invalid_argument("Incorrect number of parameters");

    // read value
    std::uint32_t value;
    std::cin >> value;

    if (v[0].type != token_type::REG)
        throw std::invalid_argument("Invalid argument type");

    // save it
    _rf[v[0].value] = value;

    return Token {"nil", token_type::NIL};
}

const Token ALU::read_char(const std::vector<Token> & v) {
    // read value
    char value;
    std::cin >> value;

    // std::cout << "val " << value;

    if (v[0].type != token_type::REG)
        throw std::invalid_argument("Invalid argument type");

    // save it
    _rf[v[0].value] = static_cast<std::uint32_t>(value);

    return Token {"nil", token_type::NIL};
}

const Token ALU::exit(const std::vector<Token> & v) {
    // TODO: exit functionality
    for (auto [val, _] : v)
        std::cout << val << ' ';

    return Token {"nil", token_type::NIL};
}



/* AUX FUNCTIONS */

bool ALU::_to_bool(const Token & token) const {
    if (token.type != token_type::BOOL) {
        throw std::invalid_argument("Invalid argument type(s)");
    }

    if (token.value == "true")
        return true;
    else if (token.value == "false")
        return false;
    else
        throw std::invalid_argument(std::format("Invalid BOOL token value '{}'", token.value));
}



int ALU::_to_num(const Token & token) const {
    if (token.type != token_type::NUM) {
        throw std::invalid_argument("Invalid argument type(s)");
    }

    return stoi(token.value);
}
