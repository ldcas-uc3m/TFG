#include <iostream>

#include "cpu/register_file.hpp"
#include "cpu/interpreter/interpreter.hpp"
#include "memory/text.hpp"



int main() {

    RegisterFile reg_file {"t0", "t1", "t2", "t3", "t4", "t5"};

    // reg_file["t0"] = -69;

    // std::cout << reg_file << std::endl;

    // reg_file.setdmode(dmode::SIG);
    // std::cout << reg_file << std::endl;

    // reg_file.setdmode(dmode::USG);
    // std::cout << reg_file << std::endl;

    Memory::Instruction i0 = "(+ 1 2)";
    Memory::Instruction i1 = "(+ (+ 1 2) (+ 1 3))";
    Memory::Instruction i2 = "(+ (+ 1 2) (+ 1 3)";

    Interpreter interp {reg_file};

    interp.exec(i0);

    std::cout << std::endl;

    interp.exec(i1);

    // interp.exec(i2);

}