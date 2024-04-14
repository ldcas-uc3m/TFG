#ifndef STRING_MANIPULATION_HPP
#define STRING_MANIPULATION_HPP


#include <string>
#include <cstdint>


bool is_number(const std::string & s);


std::uint32_t from_hex(const std::string & s);


// trim from start (in place)
void ltrim(std::string &s);

// trim from end (in place)
void rtrim(std::string &s);

// trim from both ends (in place)
void trim(std::string &s);


void replaceAll(std::string & s, const std::string & search, const std::string & replace);


#endif