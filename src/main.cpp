#include <iostream>

#include "cpu/register_file.hpp"
#include "cpu/alu.hpp"
#include "cpu/interpreter/interpreter.hpp"
#include "memory/text.hpp"
#include "exceptions.hpp"



void test_basic(RegisterFile & reg_file, Memory::text & mem_t, Interpreter & interp) {
    std::cout << '\n' << "-------- TEST RUN --------" << '\n';


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

void test_blocks(RegisterFile & reg_file, Memory::text & mem_t, Interpreter & interp) {

    std::cout << '\n' << "-------- TEST RUN 2 --------" << '\n';

    mem_t.add_instruction("(reg! t0 (+ (reg t0) 1))");  // ADDI t0, t0, 1
    mem_t.add_instruction("(do (reg! t0 1) (reg! t1 (+ (reg t0) 1)))");
    mem_t.add_instruction("(if (> (reg t1) (reg t0)) (reg! t2 69))");
    mem_t.add_instruction("(if (> (reg t1) (reg t0)) ())");

    std::cout << ".text" << '\n' << mem_t;

    int i = 0;
    while (true) {
        std::cout << '\n' << "----" << '\n';
        std::cout << "CYCLE " << i;
        std::cout << '\n' << "----" << '\n';
        std::cout << "Instruction: " << mem_t.get_instuction(reg_file.pc) << "\n\n";

        if (!interp.next()) {
            std::cout << reg_file << std::endl;
            break;
        }

        std::cout << reg_file << std::endl;

        ++i;
    }
}


void test_syscalls(RegisterFile & reg_file, Memory::text & mem_t, Interpreter & interp) {

    std::cout << '\n' << "-------- TEST RUN 3 --------" << '\n';

    mem_t.add_instruction("(call 0 42)");
    mem_t.add_instruction("(call 1 70)");  // 'F'
    mem_t.add_instruction("(call 1 10)");  // '\n' (LF)
    mem_t.add_instruction("(call 2 t0)");
    mem_t.add_instruction("(call 3 t1)");

    std::cout << ".text" << '\n' << mem_t;

    while (interp.next()) {}

    std::cout << reg_file << std::endl;
}



int main() {
    std::uint32_t start_addr = 0;

    RegisterFile reg_file {start_addr, {"t0", "t1", "t2", "t3", "t4", "t5"}};
    Memory::text mem_t {start_addr};

    Interpreter interp {
        reg_file,
        mem_t,
        {
            {"0", "print_int" },
            {"1", "print_char" },
            {"2", "read_int" },
            {"3", "read_char" },
            {"4", "exit"}
        }
    };

    try {
        test_basic(reg_file, mem_t, interp);

        mem_t.purge();

        test_blocks(reg_file, mem_t, interp);

        mem_t.purge();

        // test_syscalls(reg_file, mem_t, interp);

        std::cout << std::endl;

        std::cout << '\n' << "-------- EXEC RUN --------" << '\n';
        interp.exec("(if (> (reg t1) (reg t0)) ())");
    }
    catch (LUISPDAException &e) {
        std::cout << "[" << e.type << "] " << e.what() << std::endl;

        return -1;
    }
    catch (MEMException &e) {
        std::cout << "[" << e.type << "] " << e.what() << std::endl;
        std::cout << ".text" << '\n' << mem_t;

        return -1;
    }
    catch (RFException &e) {
        std::cout << "[" << e.type << "] " << e.what() << std::endl;
        std::cout << reg_file << std::endl;

        return -1;
    }
    catch (TFGException &e) {
        std::cout << "[" << e.type << "] " << e.what() << std::endl;

        return -1;
    }



    return 0;

}