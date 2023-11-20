#include "alu.hpp"

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <stdexcept>

#include "interpreter/ast.hpp"
#include "exceptions.hpp"
#include "memory/text.hpp"
#include "register_file.hpp"




const Token ALU::add(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    int result = to_num(v[0]) + to_num(v[1]);

    return from_num(result);
}


const Token ALU::sub(const std::vector<Token> & v) {
    if (v.size() == 2) {
        int result = to_num(v[0]) - to_num(v[1]);
        return from_num(result);
    }
    else if (v.size() == 1) {
        int result = - to_num(v[0]);
        return from_num(result);
    }
    else
        throw std::invalid_argument("Incorrect number of parameters");
}


const Token ALU::mul(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    int result = to_num(v[0]) * to_num(v[1]);

    return from_num(result);
}


const Token ALU::div(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    int result = to_num(v[0]) / to_num(v[1]);

    return from_num(result);
}


const Token ALU::mod(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    int result = to_num(v[0]) % to_num(v[1]);

    return from_num(result);
}


const Token ALU::gt(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    bool result = to_num(v[0]) > to_num(v[1]);

    return from_bool(result);
}


const Token ALU::lt(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    bool result = to_num(v[0]) < to_num(v[1]);

    return from_bool(result);
}


const Token ALU::get(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    bool result = to_num(v[0]) >= to_num(v[1]);

    return from_bool(result);
}


const Token ALU::let(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    bool result = to_num(v[0]) <= to_num(v[1]);

    return from_bool(result);
}


const Token ALU::eq(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    bool result = to_num(v[0]) == to_num(v[1]);

    return from_bool(result);
}


const Token ALU::neq(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 2) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    bool result = to_num(v[0]) != to_num(v[1]);

    return from_bool(result);
}


const Token ALU::neg(const std::vector<Token> & v) {
    // check parameters
    if (v.size() != 1) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    bool result = !to_bool(v[0]);

    return from_bool(result);
}



const Token ALU::get_register (const std::vector<Token> & v) {
    if (v.size() != 1) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    if (v[0].type != token_type::REG) {
        throw std::invalid_argument("Invalid argument type");
    }


    std::uint32_t result;
    try {
        result = _rf[v[0].value];
    }
    catch (std::out_of_range &e) {
        throw LUISPDAException("Register " + v[0].value + " not found.");
    }

    return Token {std::to_string(result), token_type::NUM};
}


const Token ALU::set_register (const std::vector<Token> & v) {
    if (v.size() != 2) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    if (v[0].type != token_type::REG || v[1].type != token_type::NUM) {
        throw std::invalid_argument("Invalid argument type");
    }

    std::uint32_t value = static_cast<std::uint32_t>(stoi(v[1].value));
    _rf[v[0].value] = value;

    return Token {std::to_string(value), token_type::NUM};
}



const Token ALU::get_pc (const std::vector<Token> & v) {
    if (v.size() != 0) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    return Token {std::to_string(_rf.pc), token_type::NUM};
}

const Token ALU::set_pc (const std::vector<Token> & v) {
    if (v.size() != 1) {
        throw std::invalid_argument("Incorrect number of parameters");
    }

    if (v[0].type != token_type::NUM) {
        throw std::invalid_argument("Invalid argument type");
    }

    _rf.pc = static_cast<std::uint32_t>(stoi((v[0].value)));

    return Token {std::to_string(_rf.pc), token_type::NUM};
}



bool ALU::to_bool(const Token & token) const {
    if (token.type != token_type::BOOL) {
        throw std::invalid_argument("Invalid argument type(s)");
    }

    if (token.value == "true")
        return true;
    else if (token.value == "false")
        return false;
    else
        throw std::invalid_argument("Invalid BOOL token value '" + token.value + "'");
}



int ALU::to_num(const Token & token) const {
    if (token.type != token_type::NUM) {
        throw std::invalid_argument("Invalid argument type(s)");
    }

    return stoi(token.value);
}
