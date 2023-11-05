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

#include "../exceptions.hpp"




/* Register File Display mode */
enum class dmode {
    HEX,  // hexadecimal
    SIG,  // signed
    USG   // unsigned
};


class RegisterFile {

    public:

        /* constructor */
        RegisterFile(std::initializer_list<std::string> l) : _reg_names{l} {
            // fill up register map
            for (int i = 0; i < _reg_names.size(); ++i) {
                _reg_map.insert({_reg_names[i], i});
            }

            _rf.resize(_reg_names.size());
        }


        /**
        * @brief checks if a register exists
        */
        bool exists(std::string const & r) {
            return std::find(_reg_names.begin(), _reg_names.end(), r) != _reg_names.end();
        }

        bool exists(int index) {
            return index < _reg_names.size();
        }


        /* overload []  operator */

        std::uint32_t & operator[] (int index) {
            try {
                return _rf[index];
            }
            catch (std::out_of_range e) {
                throw LUISPDAException("Register " + std::to_string(index) + " not found.");
            }
        }

        std::uint32_t & operator[] (std::string const & r) {
            try {
                return _rf[_reg_map.at(r)];
            }
            catch (std::out_of_range e) {
                throw LUISPDAException("Register " + r + " not found.");
            }
        }

        // (usefull when passing RegisterFile by constant reference)
        const std::uint32_t & operator[] (int index) const {
            try {
                return _rf[index];
            }
            catch (std::out_of_range e) {
                throw LUISPDAException("Register " + std::to_string(index) + " not found.");
            }
        }

        const std::uint32_t & operator[] (std::string const & r) const {
            try {
                return _rf[_reg_map.at(r)];
            }
            catch (std::out_of_range e) {
                throw LUISPDAException("Register " + r + " not found.");
            }
        };


        /* overload << operator */
        friend std::ostream & operator << (std::ostream & out, RegisterFile const & rf) {

            // print all registers
            for (int i = 0; i < rf._reg_names.size(); ++i) {

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

            return out;
        }


        void setdmode(dmode dmode) { _dmode = dmode; }


    private:

        std::vector<std::uint32_t> _rf;  // vector with register values
        std::map<std::string, int> _reg_map;  // map between register names and register indexes
        std::vector<std::string> _reg_names;  // map between register indexes and register names

        dmode _dmode = dmode::HEX;  // display mode

};


#endif