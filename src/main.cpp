#include <iostream>

#include "cpu/register_file.hpp"
#include "cpu/interpreter.hpp"
#include "memory/text.hpp"



int main() {

    // RegisterFile reg_file {"t0", "t1", "t2", "t3", "t4", "t5"};

    // reg_file["t0"] = -69;

    // std::cout << reg_file << std::endl;

    // reg_file.setdmode(rfdmode::SIG);
    // std::cout << reg_file << std::endl;

    // reg_file.setdmode(rfdmode::USG);
    // std::cout << reg_file << std::endl;

    Memory::Instruction i0 = "(ADDI 1 2)";
    Memory::Instruction i1 = "(ADDI (ADDI 1 2) (ADDI 1 3))";
    Memory::Instruction i2 = "(ADDI (ADDI 1 2) (ADDI 1 3)";

    Interpreter interp {};

    interp.exec(i0);
    interp.exec(i1);
    // interp.exec(i2);

    std::cout << "Done" << std::endl;

}