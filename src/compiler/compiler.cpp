#include "compiler.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <iostream>

#include <nlohmann/json.hpp>

#include "lib/string_manipulation.hpp"


using json = nlohmann::json;



void Compiler::parse_data(std::ifstream & file) {

}

void Compiler::parse_text(std::ifstream & file) {
    std::string line;

    while (!file.eof()) {
        // TODO: tags
        getline(file, line);
        trim(line);

        std::istringstream line_iss(line);  // transform into input string stream to read word by word
        std::string word;

        // load instruction
        line_iss >> word;  // read word
        json instruction = _inst_set.at(word);  // TODO: catch exception

        // load definition
        auto def = instruction.at("def").get<std::string>();

        // load and replace args
        auto args = instruction.at("args").get<std::vector<std::string>>();
        for (auto & arg : args) {
            line_iss >> word;  // get value

            replaceAll(def, arg, word);  // replace arguments
        }
        // TODO: enforce $ at start of arg rule

        _mem_t.add_instruction(def);

        // TODO: give an end
    }
    return;
}



void Compiler::compile_file(std::ifstream & file) {

    if (!file.is_open()) return;  // TODO: throw error

    std::string line;

    while (!file.eof()) {
        getline(file, line);
        trim(line);

        if (line == "") continue;
        else if (line == ".text")
            parse_text(file);

        else if (line == ".data")
            parse_data(file);

        // TODO: prevent double data, double text
        return;
    }

    return;

}
