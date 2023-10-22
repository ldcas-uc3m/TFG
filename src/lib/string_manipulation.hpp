#include <string>
#include <vector>
#include <algorithm>


bool is_number(const std::string & s) {
    /*
    Evaluates if a string is a number
    */
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
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


