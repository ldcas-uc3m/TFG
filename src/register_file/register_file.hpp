#ifndef REGISTER_FILE_HPP
#define REGISTER_FILE_HPP


#include <cstdint>
#include <vector>
#include <ostream>
#include <initializer_list>
#include <string>
#include <map>



class RegisterFile {

    public:
        // constructor
        RegisterFile(std::initializer_list<std::string> l) : _reg_names{l} {
            // fill up register map
            for (int i = 0; i < _reg_names.size(); ++i) {
                _reg_map.insert({_reg_names[i], i});
            }

            _rf.resize(_reg_names.size());
        }


        // overload []  operator
        std::uint32_t & operator[] (int index) {
            return _rf[index];
        }

        std::uint32_t & operator[] (std::string const & r) {
            return _rf[_reg_map[r]];
        }


        // overload << operator
        friend std::ostream & operator << (std::ostream & out, RegisterFile const & rf) {
            for (int i = 0; i < rf._reg_names.size(); ++i) {
                out << rf._reg_names[i] << ": " << rf._rf[i] << '\t';
            }

            return out;
        }

    private:

        std::vector<std::uint32_t> _rf;  // vector with register values
        std::map<std::string, int> _reg_map;  // map between register names and register indexes
        std::vector<std::string> _reg_names;  // map between register indexes and register names

};




#endif