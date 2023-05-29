#ifndef SHAPE_H
#define SHAPE_H

#include "../utility/LynType.h"
#include "../utility/ProgramState.h"

// == Declaration == //

class Shape
{
public:
    virtual std::string Info();
    virtual Area_t GetArea();
};

// == Implementation == //

// Display shape info
std::string Shape::Info()
{
    std::string info("Shape [");
    info.append(std::to_string(GetArea()));
    info.append("]");
    return info;
}

// Return shape area
Area_t Shape::GetArea()
{
    STATE::ALR("The `GetArea()` of an empty `Shape` object is called.");
    return 0;
}

#endif