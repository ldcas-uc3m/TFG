#include <iostream>

#include "cpu/register_file.hpp"
#include "cpu/alu.hpp"
#include "cpu/interpreter/interpreter.hpp"
#include "memory/text.hpp"
#include "exceptions.hpp"



int main() {
    std::uint32_t start_addr = 0;

    RegisterFile reg_file {start_addr, {"t0", "t1", "t2", "t3", "t4", "t5"}};
    Memory::text mem_t {start_addr};

    Interpreter interp {reg_file, mem_t};


    mem_t.add_instruction("(+ 1 2)");
    mem_t.add_instruction("(+ (+ 1 2) (+ 1 3))");
    mem_t.add_instruction("(reg t0)");
    mem_t.add_instruction("(reg! t0 (+ (reg t0) 1))");  // ADDI t0, t0, 1
    mem_t.add_instruction("(pc! 0)");  // j 0x00000000

    std::cout << mem_t << std::endl;


    try {

        interp.exec();
        interp.exec();
        interp.exec();
        interp.exec();
        interp.exec();
        interp.exec();
    }
    catch (TFGException e) {
        std::cout << '[' << e.type() << "] " << e.what() << std::endl;
        return -1;
    }

    std::cout << std::endl;

    reg_file.setdmode(dmode::SIG);
    std::cout << reg_file << std::endl;
}