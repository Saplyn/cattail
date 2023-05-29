#ifndef STASK_EXCEPTION_H
#define STASK_EXCEPTION_H

#include <stdexcept>

// == Declaration == //

class StackOverflow : public std::overflow_error
{
public:
    StackOverflow(const std::string& _msg) :
        std::overflow_error(_msg) {}
};

class StackUnderflow : public std::underflow_error
{
public:
    StackUnderflow(const std::string& _msg) :
        std::underflow_error(_msg) {}
};

// == Implementation == //

#endif