#ifndef STRING_MANIPULATION_HPP
#define STRING_MANIPULATION_HPP


#include <string>
#include <vector>
#include <algorithm>
#include <regex>


static bool is_number(const std::string & s) {
    /*
    Evaluates if a string is a number
    */
    // return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    return std::regex_match(s, std::regex("-?[0-9]+"));
}



#endif