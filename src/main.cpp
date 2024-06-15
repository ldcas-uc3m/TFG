#include <iostream>
#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

#include "cpu/register_file.hpp"
#include "cpu/alu.hpp"
#include "cpu/control_unit/control_unit.hpp"
#include "memory/text.hpp"
#include "exceptions/exceptions.hpp"
#include "compiler/compiler.hpp"
#include "lib/string_manipulation.hpp"


using json = nlohmann::json;



void repl(Interpreter & interp, RegisterFile & reg_file, Memory::data & mem_d) {
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



int main() {
    // std::uint32_t start_addr_t = 0x00000000;
    // std::uint32_t start_addr_d = 0x00000100;
    // std::uint32_t end_addr_d   = 0xFFFFFFFF;

    // RegisterFile reg_file {start_addr_t, {"t0", "t1", "t2", "t3", "t4", "t5"}};
    // Memory::data mem_d {start_addr_d, end_addr_d};
    // Memory::text mem_t {start_addr_t};

    // Interpreter interp {
    //     reg_file,
    //     mem_t,
    //     mem_d,
    //     {
    //         {"0", "print_int"},
    //         {"1", "print_char"},
    //         {"2", "read_int"},
    //         {"3", "read_char"},
    //         {"4", "exit"}
    //     }
    // };

    std::string ARCH_FILE = "../../architectures/RISC-V.json";
    std::string ASM_FILE = "../../examples/tmp.riscv";

    // load file
    std::ifstream file {ARCH_FILE};
    json arch(json::parse(file, nullptr, true, true));

    // get data
    std::uint32_t start_addr_t = from_hex(arch.at("memory").at("text").at("start_addr").get<std::string>());
    std::uint32_t start_addr_d = from_hex(arch.at("memory").at("data").at("start_addr").get<std::string>());
    std::uint32_t end_addr_d = from_hex(arch.at("memory").at("data").at("end_addr").get<std::string>());

    auto registers = arch.at("registers").get<std::vector<std::string>>();
    auto syscalls = arch.at("syscalls").get<std::unordered_map<std::string, std::string>>();
    json inst_set = arch.at("instruction_set");
    json data_types = arch.at("data_types");
    char comment_char = *arch.at("comment_char").get<std::string>().begin();

    // initialize simulator
    RegisterFile reg_file {start_addr_t, registers};
    Memory::data mem_d {start_addr_d, end_addr_d};
    Memory::text mem_t {start_addr_t};

    Interpreter interp {reg_file, mem_t, mem_d, syscalls};
    Compiler comp {inst_set, data_types, mem_d, mem_t, comment_char};


    try {
        // repl(interp, reg_file, mem_d);

        std::ifstream asm_file {ASM_FILE};
        comp.compile_file(asm_file);
        std::cout << ".text" << '\n' << mem_t << std::endl;

        // return 0;
        while(interp.next()) {
            std::cout << reg_file << '\n';
        }


    }
    catch (StopExecution &e) {
        std::cout << "[" << e.type << "] " << e.what() << std::endl;
        return 0;
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