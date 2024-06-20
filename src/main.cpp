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



void repl(Interpreter & interp) {
    std::string inst;
    std::cin.ignore();  // as we've used std::cin >> before

    std::cout << "Welcome to the REPL enviroment!\n\nType 'x' to exit\n";
    while (true) {
        std::cout << "> " << std::flush;
        std::getline(std::cin, inst);
        std::cout << std::endl;

        if (inst == "x") break;

        try {
            interp.exec(inst);
        }
        catch (StopExecution &e) {
            std::cout << "[" << e.type << "] " << e.what() << std::endl;
            continue;
        }
        catch (MEMException &e) {
            std::cout << "[" << e.type << "] " << e.what() << std::endl;
            continue;
        }
        catch (RFException &e) {
            std::cout << "[" << e.type << "] " << e.what() << std::endl;
            continue;
        }
        catch (LUISPDAException &e) {
            std::cout << "[" << e.type << "] " << e.what() << std::endl;
            continue;
        }
    }
}



/* CLI ACTIONS */


enum class action {
    load,
    stop,
    next,
    repl,
    run,
    reg,
    mem_t,
    mem_d,
    fmt,
    exit,
    help,
    na
};


constexpr action parse_action(std::string const & str) {
    if (str.length() != 1) return action::na;

    if (str == "p") return action::load;
    if (str == "s") return action::stop;
    if (str == "n") return action::next;
    if (str == "e") return action::repl;
    if (str == "f") return action::run;
    if (str == "r") return action::reg;
    if (str == "t") return action::mem_t;
    if (str == "d") return action::mem_d;
    if (str == "c") return action::fmt;
    if (str == "x") return action::exit;
    if (str == "h") return action::help;

    return action::na;
}




int main(int argc, char *argv[]) {

    /* PARSE ARGUMENTS */

    if (argc != 2) {
        std::cerr << "Incorrect number of arguments." << "\n\n";
        std::cout << "Usage:\n  " << argv[0] << " --isa=ISA_FILE" << "\n";

        return -1;
    }

    auto isa_file = std::string(argv[1]);

    if (isa_file.rfind("--isa=", 0) == 0) {
        isa_file = isa_file.substr(6);
    } else {
        std::cerr << "Incorrect arguments." << "\n\n";
        std::cout << "Usage:\n  " << argv[0] << " --isa=ISA_FILE" << "\n";
        return -1;
    }


    /* LOAD ARCH */

    // TODO: validate file exists, is valid JSON, etc.

    // load file
    std::ifstream file {isa_file};
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

    reg_file.setdmode(dmode::HEX);


    /* MAIN CLI */

    // const std::string ASM_FILE = "../../examples/tmp.riscv";

    const std::string ACTION_HELP_TEXT =
        "p - load program\n"
        "s - stop program\n"
        "n - execute next instruction\n"
        "e - enter REPL environment\n"
        "f - full run\n"
        "r - show registers\n"
        "t - show text memory\n"
        "d - show data memory\n"
        "c - change format\n"
        "x - exit\n"
        "h - help\n"
        "\n"
    ;

    std::cout << "Simulator loaded!\n\nEnter 'h' in order to view a list of options\n";

    std::string action;
    bool programLoaded = false;

    while (true) {
        try {
            std::cout << ": ";
            std::cin >> action;

            switch (parse_action(action)) {
                case action::load: {
                    if (programLoaded) {
                        std::cout << "A program is already executing. Stop the execution\n";
                        break;
                    }

                    std::cout << "Enter the program file:\n> ";

                    std::string file;
                    std::cin.ignore();
                    std::getline(std::cin, file);

                    std::ifstream asm_file {file};
                    Memory::Address main_addr = comp.compile_file(asm_file);
                    reg_file.pc = main_addr;

                    programLoaded = true;
                    std::cout << "Program loaded!\n";
                    break;
                }

                case action::stop:
                    // reset
                    mem_t.clear();
                    mem_d.clear();
                    reg_file.clear();

                    std::cout << "Simulator reset!\n";
                    break;

                case action::next:
                    if (!programLoaded) {
                        std::cout << "There is no program loaded!\n";
                        break;
                    }

                    interp.next();
                    break;


                case action::repl:
                    repl(interp);
                    break;

                case action::run:
                    try {
                        while (interp.next()) {}
                    } catch (StopExecution &e) {}
                    break;

                case action::reg:
                    std::cout << reg_file;
                    break;

                case action::mem_t:
                    std::cout << ".text" << '\n' << mem_t;
                    break;

                case action::mem_d:
                    std::cout << ".data" << '\n' << mem_d;
                    break;

                case action::fmt: {
                    std::string format;
                    std::cout << "Select the format:\n"
                    "  - h: hexadecimal\n"
                    "  - u: unsigned\n"
                    "  - s: signed\n"
                    "> ";
                    std::cin >> format;

                    if (format == "h") reg_file.setdmode(dmode::HEX);
                    else if (format == "u") reg_file.setdmode(dmode::USG);
                    else if (format == "s") reg_file.setdmode(dmode::SIG);
                    else std::cout << "Unknown format\n";

                    break;
                }

                case action::exit:
                    return 0;

                case action::help:
                    std::cout << ACTION_HELP_TEXT;
                    break;

                case action::na:
                    std::cout << "Unknown action.\n" << ACTION_HELP_TEXT;
                    break;
            }

        }
        // catch (StopExecution &e) {
        //     std::cout << "[" << e.type << "] " << e.what() << std::endl;
        //     return 0;
        // }
        catch (MEMException &e) {
            std::cout << "[" << e.type << "] " << e.what() << std::endl;
        }
        catch (RFException &e) {
            std::cout << "[" << e.type << "] " << e.what() << std::endl;
        }
        catch (LUISPDAException &e) {
            std::cout << "[" << e.type << "] " << e.what() << std::endl;
        }
        catch (TFGException &e) {
            std::cout << "[" << e.type << "] " << e.what() << std::endl;
            return -1;
        }

    }


    return 0;

}