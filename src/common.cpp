#include "common.hpp"

string toUpper(const std::string &str)
{
    string ret(str);
    std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
    return ret;
}