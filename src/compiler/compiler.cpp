#include "compiler.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <format>

#include <iostream>

#include <nlohmann/json.hpp>

#include "lib/string_manipulation.hpp"
#include "exceptions/exceptions.hpp"


using json = nlohmann::json;

constexpr auto zero_terminator = static_cast<Memory::Value>('\0');



std::string Compiler::parse_data(std::ifstream & file) {
    std::string line;
    Memory::Address addr = _mem_d.start_addr;

    while (!file.eof()) {
        _curr_line++;
        getline(file, line);
        trim(line);

        if (line.front() == '.') return line;
        if (line.length() == 0) continue;
        if (*line.begin() == _comment_char) continue;

        std::istringstream line_iss(line);  // transform into input string stream to read word by word
        std::string tag;

        // read tag
        line_iss >> tag;

        if (tag.back() == ':') {
            tag.pop_back();  // remove :
        }
        else throw CompilerException(std::format("Line {}: Expected ':'", _curr_line));


        // read data type
        std::string word;
        line_iss >> word;

        if (word == _data_types.at("word").get<std::string>()) {
            // get value
            Memory::Value value;
            line_iss >> word;
            if (word.size() > 1 && word[0] == '0' && word[1] == 'x') value = from_hex(word);
            else value = stoi(word);

            _mem_d.set_value(addr, value);  // store value

            auto [_, inserted] = _tags.insert({tag, addr});  // save tag
            if (!inserted) throw CompilerException(std::format("Line {}: Duplicate tag '{}'", _curr_line, tag));
            addr += Memory::WORD_SIZE;
        }
        else if (word == _data_types.at("str").get<std::string>()) {
            while (line_iss.peek() == ' ') {line_iss.get();};  // skip whitespace
            char a = line_iss.get();
            if (a != '"') throw CompilerException(std::format("Line {}: Expected '\"'", _curr_line));

            // load string in memory
            char c;
            Memory::Value value;
            bool end = false;  // checks the string was properly terminated
            Memory::Address sub_addr = addr;

            while (line_iss) {
                c = line_iss.get();
                if (c == '"') {
                    end = true;
                    break;
                }

                value = static_cast<Memory::Value>(c);  // convert to int
                _mem_d.set_value(sub_addr, value);  // store value
                sub_addr += Memory::WORD_SIZE;
            }

            if (!end) throw CompilerException(std::format("Line {}: Expected '\"'", _curr_line));
            _mem_d.set_value(sub_addr, zero_terminator);  // store zero terminator
            sub_addr += Memory::WORD_SIZE;

            auto [_, inserted] = _tags.insert({tag, addr});  // save tag
            if (!inserted) throw CompilerException(std::format("Line {}: Duplicate tag '{}'", _curr_line, tag));
            addr += sub_addr;  // restore addr
        }
        else
            throw CompilerException(std::format("Line {}: Unknown directive '{}'", _curr_line, word));
    }

    throw CompilerException("Line " + std::to_string(_curr_line) + ": No .text found");
}


Memory::Address Compiler::parse_text(std::ifstream & file) {
    std::string line;

    std::vector<std::string> inst_v;  // place to temporary save instructions until all tags are read
    Memory::Address addr = 0;
    Memory::Address main_addr = 0;

    while (!file.eof()) {
        _curr_line++;
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

            auto [_, inserted] = _tags.insert({word, addr});  // save address of next instruction
            if (!inserted) throw CompilerException(std::format("Line {}: Duplicate tag '{}'", _curr_line, word));

            if (word == "main") main_addr = addr;  // save main addr
            continue;
            // TODO: enforce requirement of main tag
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

        // TODO: enforce $ at start of arg rule

        inst_v.push_back(def);
        addr += Memory::WORD_SIZE;

        // TODO: give an end
    }

    // add instructions and tags
    for (auto & inst : inst_v) {
        // replace tags
        for (const auto & [tag, addr] : _tags) {
            replaceAll(inst, tag, std::format("{:#010x}", addr));
        }
        _mem_t.add_instruction(inst);
    }


    return main_addr;
}



Memory::Address Compiler::compile_file(std::ifstream & file) {

    if (!file.is_open()) throw CompilerException("File error");

    std::string line;

    // TODO: refactor this

    while (!file.eof()) {
        getline(file, line);
        trim(line);

        if (line.length() == 0) continue;
        if (*line.begin() == _comment_char) continue;

        else if (line == ".data") {
            line = parse_data(file);
            if (line == ".text") {
                for (const auto& [tag, value] : _tags) std::cout << tag << ": " << std::hex << value << "\n";
                return parse_text(file);
            }
        }

        else if (line == ".text")
            return parse_text(file);
    }

    throw CompilerException("Line " + std::to_string(_curr_line) + ": No .text found");

}
