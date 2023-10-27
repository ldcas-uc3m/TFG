#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>
#include <cstdint>
#include <map>
#include <iomanip>
#include <vector>
#include <ostream>




// TODO: memory as a template? different types of memory with different initializers?

namespace Memory {

    // TODO: export this
    constexpr int WORD_SIZE = 4;  // Bytes

    using Instruction = std::string;
    using Address = std::uint32_t;


    class text {
    /*
    LUISP-DA instruction definition
    */
        public:
            text(Address start_addr) : _inst {} {
                _curr_addr = start_addr;
            }

            // TODO: overload with []
            const Instruction & get_instuction(Address addr) {
                return _inst_map[addr];
            }

            void add_instruction(Instruction inst) {
                _inst_map.insert({ _curr_addr, inst });

                _curr_addr += WORD_SIZE;

            }

            // overload << operator
            friend std::ostream & operator << (std::ostream & out, text const & text) {
                /*
                Prints all current instructions
                */
                for(const auto& elem : text._inst_map) {
                    out << "0x" << std::setfill('0') << std::setw(8) << std::right << std::hex << elem.first;
                    out << '\t';
                    out << elem.second;
                    out << '\n';
                }
                return out;
            }
        
        private:
            std::vector<Instruction> _inst;  // instructions
            Address _curr_addr;  // current last address
            std::map<Address, Instruction> _inst_map;  // map between addreses and instructions
    };
}


#endif