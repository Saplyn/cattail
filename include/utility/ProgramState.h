#ifndef PROGRAME_STATE_H
#define PROGRAME_STATE_H

#include <string>
#include <iostream>

// == Declaration == //

enum VLevel
{
    Silent = 0,
    Report = 1,
    Concise = 2,
    Detailed = 3
};

namespace STATE
{
    VLevel verbose = VLevel::Report;
    bool color = true;
    
    void SetVerbose(VLevel _value = VLevel::Concise);
    void SetColor(bool _value = true);
    void LOG(VLevel _lvl, std::string _msg);
    void ERR(std::string _msg);
    void ALR(std::string _msg);
};

// == Implementation == //

void STATE::SetVerbose(VLevel _level)
{
    verbose = _level;
}

void STATE::SetColor(bool _value)
{
    color = _value;
}

void STATE::LOG(VLevel _lvl, std::string _msg)
{
    if (verbose >= _lvl)
    {
        if (color) { std::cerr << "\033[2m"; }
        std::cerr << "[DEBUG] " << _msg;
        if (color) { std::cerr << "\033[0m"; }
        std::cerr << std::endl;
    }
}

void STATE::ERR(std::string _msg)
{
    if (verbose >= VLevel::Report)
    {
        if (color) { std::cerr << "\033[91m"; }
        std::cerr << "[ERROR] " << _msg;
        if (color) { std::cerr << "\033[0m"; }
        std::cerr << std::endl;
    }
}

void STATE::ALR(std::string _msg)
{
    if (verbose >= VLevel::Report)
    {
        if (color) { std::cerr << "\033[33m"; }
        std::cerr << "[ALERT] " << _msg;
        if (color) { std::cerr << "\033[0m"; }
        std::cerr << std::endl;
    }
}

#endif