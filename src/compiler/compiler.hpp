#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <fstream>
#include <unordered_map>
#include <cstdint>

#include <nlohmann/json.hpp>

#include "memory/text.hpp"
#include "memory/data.hpp"


using json = nlohmann::json;



class Compiler final {
    public:
        Compiler(
            json inst_set,
            json data_types,
            Memory::data & mem_d,
            Memory::text & mem_t,
            char comment_char
        ):
            _mem_t {mem_t},
            _mem_d {mem_d},
            _comment_char {comment_char},
            _tags {}
        {
            _inst_set = inst_set;  // json needs to be initialized like this
            _data_types = data_types;
        }


        Memory::Address compile_file(std::ifstream & file);

    private:
        json _inst_set;
        json _data_types;
        Memory::text & _mem_t;
        Memory::data & _mem_d;
        char _comment_char;
        int _curr_line = 1;

        std::unordered_map<std::string, Memory::Address> _tags;

        /**
        * @brief parses a data segment
        * @return The next line starting w/ a directive ('.')
        */
        std::string parse_data(std::ifstream & file);

        /**
        * @brief parses a text segment
        * @return The main start address
        */
        Memory::Address parse_text(std::ifstream & file);
};



#endif