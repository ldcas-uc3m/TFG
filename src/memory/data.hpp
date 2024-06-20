#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <cstdint>
#include <map>
#include <iomanip>
#include <vector>
#include <iostream>
#include <ostream>
#include <format>

#include "exceptions/exceptions.hpp"




namespace Memory {

    using Value = std::uint32_t;
    using Address = std::uint32_t;


    class data {
        public:
            data(Address start_addr, Address end_addr)
            :
                start_addr {start_addr},
                end_addr {end_addr},
                _data_map {}
            {}

            const Value & get_value(Address addr) const {
                _validateAddress(addr);

                try {
                    return _data_map.at(addr);
                }
                catch (std::out_of_range & e) {
                    throw MEMException(std::format(".data Segmentation fault. Requested addr: {:#010x}.", addr));
                }

            }

            void set_value(Address addr, Value val) {
                _validateAddress(addr);

                _data_map.insert({ addr, val });

            }

            void clear() { _data_map.clear(); }


            // overload << operator
            friend std::ostream & operator << (std::ostream & out, data const & data) {
                /*
                Prints all current values
                */
                for(const auto & [addr, value] : data._data_map) {
                    out << "0x" << std::setfill('0') << std::setw(8) << std::right << std::hex << addr;
                    out << '\t' << "0x" << std::setfill('0') << std::setw(8) << std::right << value << '\n';
                }
                return out;
            }

            // TODO: stack & stack pointer (initialize to end_addr)

            Address start_addr;  // start address of the memory segment
            Address end_addr;  // end address of the memory segment

        private:
            // TODO: rely only on vector, not on map ('tis faster)
            std::map<Address, Value> _data_map;  // map between addreses and values


            void _validateAddress(Address addr) const {
                if (addr % WORD_SIZE != 0)
                    throw MEMException(std::format("Illegal addr {:#010x}.", addr));

                if (addr < start_addr || addr >= end_addr)
                    throw MEMException(std::format(".text Segmentation fault. Requested addr: {:#010x}.", addr));
            }

    };
}


#endif