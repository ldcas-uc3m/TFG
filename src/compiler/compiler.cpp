#include "compiler.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <format>

#include <iostream>

#include <nlohmann/json.hpp>

#include "lib/string_manipulation.hpp"


using json = nlohmann::json;




void Compiler::parse_data(std::ifstream & file) {

}


void Compiler::parse_text(std::ifstream & file) {
    std::string line;

    std::vector<std::string> inst_v;  // place to temporary save instructions until all tags are read
    Memory::Address addr = 0;

    while (!file.eof()) {
        getline(file, line);
        trim(line);

        if (line.length() == 0) continue;
        if (*line.begin() == _comment_char) continue;

        std::istringstream line_iss(line);  // transform into input string stream to read word by word
        std::string word;

        line_iss >> word;  // read word

        // check for tag (last char is :)
        if (word.back() == ':') {
            word.pop_back();  // remove :
            
            _tags.insert({word, addr});  // save address of next instruction
            continue;
        }

        // load instruction
        json instruction = _inst_set.at(word);  // TODO: catch exception

        // load definition
        auto def = instruction.at("def").get<std::string>();

        // load and replace args
        auto args = instruction.at("args").get<std::vector<std::string>>();
        for (const auto & arg : args) {
            line_iss >> word;  // get value

            replaceAll(def, arg, word);  // replace arguments
        }

        // TODO: inline comments
        // TODO: enforce $ at start of arg rule

        inst_v.push_back(def);
        addr += Memory::WORD_SIZE;

        // TODO: give an end
    }

    for (const auto & [tag, addr] : _tags) {std::cout << tag << ": " << addr << std::endl;}

    // add instructions and tags
    for (auto & inst : inst_v) {
        // replace tags
        for (const auto & [tag, addr] : _tags) {
            replaceAll(inst, tag, std::format("{:#010x}", addr));
        }
        _mem_t.add_instruction(inst);
    }

    return;

    // TODO: set PC to main
}



void Compiler::compile_file(std::ifstream & file) {

    if (!file.is_open()) return;  // TODO: throw error

    std::string line;

    while (!file.eof()) {
        getline(file, line);
        trim(line);

        if (line.length() == 0) continue;
        if (*line.begin() == _comment_char) continue;

        else if (line == ".text")
            parse_text(file);

        else if (line == ".data")
            parse_data(file);

        // TODO: prevent double data, double text
        return;
    }

    return;

}
