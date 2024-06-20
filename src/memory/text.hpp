#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>
#include <cstdint>
#include <map>
#include <iomanip>
#include <vector>
#include <iostream>
#include <ostream>
#include <format>

#include "exceptions/exceptions.hpp"




// TODO: memory as a template? different types of memory with different initializers?

namespace Memory {

    constexpr int WORD_SIZE = 4;  // Bytes  // TODO: move to memory file

    /* LUISP-DA instruction definition */
    using Instruction = std::string;
    using Address = std::uint32_t;


    class text {
        public:
            text(Address start_addr) : _inst {} {
                _curr_addr = start_addr;
                _start_addr = start_addr;
            }

            const Instruction & get_instuction(Address addr) const {
                if (addr % WORD_SIZE != 0)
                    throw MEMException(std::format("Illegal addr {:#010x}.", addr));

                if (addr >= _curr_addr)
                    throw MEMException(std::format(".text Segmentation fault. Requested addr: {:#010x}.", addr));

                return _inst_map.at(addr);
            }

            void add_instruction(Instruction inst) {
                _inst_map.insert({ _curr_addr, inst });

                _curr_addr += WORD_SIZE;
            }

            Address get_last_address() const {
                return _curr_addr;
            }


            void clear() {
                _inst_map.clear();
                _curr_addr = _start_addr;
            }

            // overload << operator
            friend std::ostream & operator << (std::ostream & out, text const & text) {
                /*
                Prints all current instructions
                */
                for(const auto & [addr, inst] : text._inst_map) {
                    out << "0x" << std::setfill('0') << std::setw(8) << std::right << std::hex << addr;
                    out << '\t'<< inst << '\n';
                }
                return out;
            }


        private:
            Address _start_addr;  // start address of the memory segment
            Address _curr_addr;  // address of the last instruction

            // TODO: rely only on vector, not on map ('tis faster)
            std::vector<Instruction> _inst;  // instructions
            std::map<Address, Instruction> _inst_map;  // map between addreses and instructions 

    };
}


#endif