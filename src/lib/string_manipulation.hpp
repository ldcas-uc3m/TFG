#ifndef STRING_MANIPULATION_HPP
#define STRING_MANIPULATION_HPP


#include <string>
#include <vector>
#include <algorithm>


bool is_number(const std::string & s) {
    /*
    Evaluates if a string is a number
    */
    // return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    return std::regex_match(s, std::regex("-?[0-9]+"));
}



size_t split_string(const std::string &txt, std::vector<std::string> &strs, char ch) {
    /*
    Splits a string by spaces into a vector
    */

    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();
}


std::vector<std::string> regex_find(const std::string & text, const std::regex & pattern) {
    /*
    Returns a vector of all matches for a specified string and parameter
    */

    std::vector<std::string> r;

    std::sregex_iterator start {text.cbegin(), text.cend(), pattern};
    std::sregex_iterator end;

    for (auto i = start; i != end; ++i) {
        std::string elem = i->str();

        // if (elem == "") continue;

        r.push_back(elem);
    }

    // std::cout << text << ": ";
    // for (const auto& i: r)
    //     std::cout << i << ';';
    // std::cout << std::endl;

    return r;
}


#endif