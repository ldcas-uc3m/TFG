#include <iostream>

#include "register_file/register_file.hpp"



int main() {


    RegisterFile reg_file {"t0", "t1"};

    std::cout << reg_file << std::endl;

    reg_file["t0"] = 69;
    std::cout << reg_file["t0"] << std::endl;

    std::cout << reg_file << std::endl;
}