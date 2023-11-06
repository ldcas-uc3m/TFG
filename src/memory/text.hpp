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

    constexpr int WORD_SIZE = 4;  // Bytes

    /* LUISP-DA instruction definition */
    using Instruction = std::string;
    using Address = std::uint32_t;


    class text {
        public:
            text(Address start_addr) : _inst {} {
                _curr_addr = start_addr;
            }

            const Instruction & get_instuction(Address addr) const {
                return _inst_map.at(addr);
            }

            void add_instruction(Instruction inst) {
                _inst_map.insert({ _curr_addr, inst });

                _curr_addr += WORD_SIZE;

            }

            const Address get_last_address() const {
                return _curr_addr;
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
            Address _curr_addr;  // current last address

            // TODO: rely only on vector, not on map ('tis faster)
            std::vector<Instruction> _inst;  // instructions
            std::map<Address, Instruction> _inst_map;  // map between addreses and instructions 

    };
}


#endif