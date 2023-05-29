#ifndef VALID_STRING_H
#define VALID_STRING_H

#include "../utility/ProgramState.h"

#include <string>
#include <sstream>

namespace VS
{
    bool IsWhiteString(std::string _str);
    bool IsNumber(std::string _str);
    int IsNumberSequence(std::string _str);
};

bool VS::IsWhiteString(std::string _str)
{
    bool fullSpace = true;
    for (auto c : _str)
    {
        if (!isblank(c))
        {
            return false;
        }
    }
    return fullSpace;
}

bool VS::IsNumber(std::string _str)
{
    STATE::LOG(VLevel::Detailed, "`IsNumber()` Checking \"" + _str + "\"");
    if (IsWhiteString(_str)) { return false; }
    try
    {
        std::size_t pos = 0;
        std::stod(_str, &pos);
        return pos == _str.length();
    }
    catch(const std::exception& e)
    {
        return false;
    }
}

int VS::IsNumberSequence(std::string _str)
{
    STATE::LOG(VLevel::Detailed, "`IsNumberSequence()` Checking \"" + _str + "\"");
    if (IsWhiteString(_str)) { return false; }
    std::stringstream ss(_str);
    std::string tmp;
    int count = 0;
    while (ss >> tmp)
    {
        if (!IsNumber(tmp))
        {
            return false;
        }
        count++;
    }
    return count;
}

#endif