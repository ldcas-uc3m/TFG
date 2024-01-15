#include <iostream>
#include <string>

#include "cpu/register_file.hpp"
#include "cpu/alu.hpp"
#include "cpu/interpreter/interpreter.hpp"
#include "memory/text.hpp"
#include "exceptions/exceptions.hpp"



int main() {
    std::uint32_t start_addr_t = 0x00000000;
    std::uint32_t start_addr_d = 0x00000100;
    std::uint32_t end_addr_d   = 0xFFFFFFFF;

    RegisterFile reg_file {start_addr_t, {"t0", "t1", "t2", "t3", "t4", "t5"}};
    Memory::data mem_d {start_addr_d, end_addr_d};
    Memory::text mem_t {start_addr_t};

    Interpreter interp {
        reg_file,
        mem_t,
        mem_d,
        {
            {"0", "print_int" },
            {"1", "print_char" },
            {"2", "read_int" },
            {"3", "read_char" },
            {"4", "exit"}
        }
    };

    try {
        std::string inst;
        while (true) {
            std::cout << "--------" << '\n';
            std::cout << reg_file << '\n';
            std::cout << ".data" << '\n' << mem_d;
            std::cout << "--------" << '\n' << '\n';

            std::cout << "Write your instruction: ";
            std::getline(std::cin, inst);

            std::cout << std::endl;

            interp.exec(inst);
        }

    }
    catch (MEMException &e) {
        std::cout << "[" << e.type << "] " << e.what() << std::endl;
        std::cout << ".text" << '\n' << mem_t;
        std::cout << ".data" << '\n' << mem_d;

        return -1;
    }
    catch (RFException &e) {
        std::cout << "[" << e.type << "] " << e.what() << std::endl;
        std::cout << reg_file << std::endl;

        return -1;
    }
    catch (LUISPDAException &e) {
        std::cout << "[" << e.type << "] " << e.what() << std::endl;

        return -1;
    }
    catch (TFGException &e) {
        std::cout << "[" << e.type << "] " << e.what() << std::endl;

        return -1;
    }


    return 0;

}