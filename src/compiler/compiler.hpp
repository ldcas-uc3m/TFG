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
            Memory::data & mem_d,
            Memory::text & mem_t
        ):
            _mem_t {mem_t},
            _mem_d {mem_d},
            _tags {}
        {
            _inst_set = inst_set;  // json needs to be initialized like this
        }


        void compile_file(std::ifstream & file);

    private:
        json _inst_set;
        Memory::text & _mem_t;
        Memory::data & _mem_d;
        std::unordered_map<std::string, std::uint32_t> _tags;


        void parse_data(std::ifstream & file);
        void parse_text(std::ifstream & file);
};



#endif