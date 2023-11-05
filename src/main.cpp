#include <iostream>

#include "cpu/register_file.hpp"
#include "cpu/alu.hpp"
#include "cpu/interpreter/interpreter.hpp"
#include "memory/text.hpp"
#include "exceptions.hpp"



int main() {

    RegisterFile reg_file {"t0", "t1", "t2", "t3", "t4", "t5"};

    ALU alu {reg_file};

    Memory::Instruction i0 = "(+ 1 2)";
    Memory::Instruction i1 = "(+ (+ 1 2) (+ 1 3))";
    Memory::Instruction i2 = "(reg t0)";
    Memory::Instruction i3 = "(reg! t0 69)";

    Interpreter interp {reg_file, alu};

    try {

        interp.exec(i0);

        std::cout << std::endl;

        interp.exec(i1);

        interp.exec(i2);

        std::cout << std::endl;

        interp.exec(i3);
    }
    catch (TFGException e) {
        std::cout << '[' << e.type() << "] " << e.what() << std::endl;
        return -1;
    }

    std::cout << std::endl;

    reg_file.setdmode(dmode::SIG);
    std::cout << reg_file << std::endl;
}