#include "string_manipulation.hpp"

#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <cctype>
#include <locale>
#include <cstdint>


bool is_number(const std::string & s) {
    /*
    Evaluates if a string is a number
    */
    // return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    return std::regex_match(s, std::regex("-?[0-9]+"));
}


std::uint32_t from_hex(const std::string & s) {
    return stoul(s, nullptr, 16);
}


// trim from start (in place)
void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}


void replaceAll(std::string & s, const std::string & search, const std::string & replace) {
    for (size_t pos = 0; ; pos += replace.length()) {
        // Locate the substring to replace
        pos = s.find(search, pos);
        if (pos == std::string::npos) break;

        // Replace by erasing and inserting
        s.erase(pos, search.length());
        s.insert(pos, replace);
    }
}
