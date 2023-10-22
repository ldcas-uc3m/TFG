#include <iostream>

#include "cpu/register_file.hpp"



int main() {


    reg_file["t0"] = -69;

    std::cout << reg_file << std::endl;

    reg_file.setdmode(rfdmode::SIG);
    std::cout << reg_file << std::endl;

    reg_file.setdmode(rfdmode::USG);
    std::cout << reg_file << std::endl;
}