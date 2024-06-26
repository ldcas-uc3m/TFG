#ifndef REGISTER_FILE_HPP
#define REGISTER_FILE_HPP


#include <cstdint>
#include <vector>
#include <ostream>
#include <initializer_list>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm>
#include <exception>

#include "exceptions/exceptions.hpp"



/* Register File Display mode */
enum class dmode {
    HEX,  // hexadecimal
    SIG,  // signed
    USG   // unsigned
    // TODO: ascii display mode
};


class RegisterFile {

    public:

        /* constructors */
        // TODO: single constructor that accepts init list and map

        RegisterFile(
            std::uint32_t pc_start_addr,
            std::initializer_list<std::string> l
        ) : pc {pc_start_addr}, _reg_names{l}, start_pc {pc_start_addr} {

            // fill up register map
            for (std::size_t i = 0; i < _reg_names.size(); ++i) {
                _reg_map.insert({_reg_names[i], i});
            }

            _rf.resize(_reg_names.size());
        }

        RegisterFile(
            std::uint32_t pc_start_addr,
            std::vector<std::string> l
        ) : pc {pc_start_addr}, _reg_names{l}, start_pc {pc_start_addr} {

            // fill up register map
            for (std::size_t i = 0; i < _reg_names.size(); ++i) {
                _reg_map.insert({_reg_names[i], i});
            }

            _rf.resize(_reg_names.size());
        }


        std::uint32_t pc;  // program counter


        /**
        * @brief checks if a register exists
        */
        bool contains(const std::string & r) const {
            return std::find(_reg_names.begin(), _reg_names.end(), r) != _reg_names.end();
        }

        bool contains(int index) const {
            return static_cast<std::size_t>(index) < _reg_names.size();
        }


        /* overload []  operator */

        std::uint32_t & operator[] (int index) {
            try {
                return _rf[index];
            }
            catch (std::out_of_range &e) {
                throw LUISPDAException("Register '" + std::to_string(index) + "' not found.");
            }
        }

        std::uint32_t & operator[] (std::string const & r) {
            try {
                return _rf[_reg_map.at(r)];
            }
            catch (std::out_of_range &e) {
                throw LUISPDAException("Register '" + r + "' not found.");
            }
        }

        // (useful when passing RegisterFile by constant reference)
        const std::uint32_t & operator[] (int index) const {
            try {
                return _rf[index];
            }
            catch (std::out_of_range &e) {
                throw LUISPDAException("Register '" + std::to_string(index) + "' not found.");
            }
        }

        const std::uint32_t & operator[] (std::string const & r) const {
            try {
                return _rf[_reg_map.at(r)];
            }
            catch (std::out_of_range &e) {
                throw LUISPDAException("Register '" + r + "' not found.");
            }
        };


        /* overload << operator */
        friend std::ostream & operator << (std::ostream & out, RegisterFile const & rf) {

            // Program Counter
            out << "PC: ";
            out << "0x" << std::setfill('0') << std::setw(8) << std::right << std::hex << rf.pc;
            out << '\n';


            // print all registers
            for (std::size_t i = 0; i < rf._reg_names.size(); ++i) {

                out << rf._reg_names[i] << ": ";

                switch (rf._dmode) {
                    case dmode::HEX:
                        out << "0x" << std::setfill('0') << std::setw(8) << std::right << std::hex << rf._rf[i];
                        break;

                    case dmode::SIG:
                        out << std::setfill(' ') << std::setw(8) << std::left << std::to_string(static_cast<int32_t>(rf._rf[i]));
                        break;

                    case dmode::USG:
                        out << 'u' << std::setfill(' ') << std::setw(8) << std::left << std::to_string(rf._rf[i]);
                        break;
                };

                out << '\t';

                // print in different lines
                if (i % 4 == 3) {
                    out << '\n';
                }
                else {
                    out << '\t';
                }
            }

            out << '\n';
            return out;
        }


        void setdmode(dmode dmode) { _dmode = dmode; }

        void clear() {
            std::fill(_rf.begin(), _rf.end(), 0);  // reset values
            pc = start_pc;
        }


    private:

        // TODO: forget about indexing with ints

        std::vector<std::uint32_t> _rf;  // vector with register values
        std::map<std::string, int> _reg_map;  // map between register names and register indexes
        const std::vector<std::string> _reg_names;  // map between register indexes and register names

        dmode _dmode = dmode::HEX;  // display mode

        std::uint32_t start_pc;

};


#endif