#include <iostream>

#include "cpu/register_file.hpp"
#include "cpu/alu.hpp"
#include "cpu/interpreter/interpreter.hpp"
#include "memory/text.hpp"
#include "exceptions.hpp"



void test_run(RegisterFile & reg_file, Memory::text & mem_t, Interpreter & interp) {
    mem_t.add_instruction("(reg! t0 (+ (reg t0) 1))");  // ADDI t0, t0, 1
    mem_t.add_instruction("(do (reg! t0 1) (reg! t1 (+ (reg t0) 1)))");
    mem_t.add_instruction("(if (> (reg t1) (reg t0)) (reg! t2 69))");
    mem_t.add_instruction("(if (> (reg t1) (reg t0)) ())");
    mem_t.add_instruction("(pc! 0)");  // j 0x00000000

    std::cout << ".text" << '\n' << mem_t;

    int NUM_CYCLES = 5;

    for (int i = 0; i < NUM_CYCLES; ++i) {


        std::cout << '\n' << "----" << '\n';
        std::cout << "CYCLE " << i;
        std::cout << '\n' << "----" << '\n';
        std::cout << "Instruction: " << mem_t.get_instuction(reg_file.pc) << "\n\n";

        interp.next();

        std::cout << reg_file << std::endl;

    }
}



int main() {
    std::uint32_t start_addr = 0;

    RegisterFile reg_file {start_addr, {"t0", "t1", "t2", "t3", "t4", "t5"}};
    Memory::text mem_t {start_addr};

    Interpreter interp {reg_file, mem_t};

    try {
        test_run(reg_file, mem_t, interp);

        std::cout << std::endl;

        interp.exec("(if (> (reg t1) (reg t0)) ())");
    }
    catch (TFGException e) {
        // TODO: make sure .type() returns the correct type
        std::cout << '[' << e.type() << "] " << e.what() << std::endl;
        return -1;
    }

}