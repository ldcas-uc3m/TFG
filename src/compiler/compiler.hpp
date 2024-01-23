#ifndef COMPILER_HPP
#define COMPILER_HPP


#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>



using json = nlohmann::json;


void test() {
    std::ifstream f("/home/ldcas/Code/TFG/architecture/RISC-V.json");
    json data = json::parse(f);

    std::cout << data << std::endl;
}











#endif