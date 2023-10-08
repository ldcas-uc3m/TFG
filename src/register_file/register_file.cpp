#include <array>
#include <map>
#include <string>
#include <cstdint>

#include "register_file.hpp"



enum Registers : int {
    t0 = 0,
    t1 = 1
};

std::map<std::string, Registers> reg_map {
    {"t0", t0}, 
    {"t1", t1} 
};

std::array<std::uint32_t, 32> rf {};


void saveToRegister(std::uint32_t value, std::string register) {
    /**
     * Stores a value to the specified register.
     * 
     * @param value Value to store.
     * @param register Name of the register.
    */

    rf[reg_map.find(register)] = value;

}


std::uint32_t getRegisterValue(std::string register) {
    /**
     * Gets the value of the specified register.
     * 
     * @param register Name of the register.
     * 
     * @return Value stored in the register.
    */

    return rf[reg_map.find(register)];
}
