#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../utility/LynType.h"
#include "../object/Shape.h"
#include "../utility/ProgramState.h"

// == Declaration == //

class Rectangle : public Shape
{
private:
    Length_t length;
    Length_t width;
public:
    Rectangle(Length_t _length, Length_t _width);
    
    std::string Info() override;
    Area_t GetArea() override;
};

// == Implementation == //

Rectangle::Rectangle(Length_t _length, Length_t _width)
{
    if (_length <= 0 || _width <= 0)
    {
        throw std::invalid_argument("length not larger than 0");
    }
    length = _length;
    width = _width;
    STATE::LOG(VLevel::Detailed, "Manually constructed a `Rectangle` instance.");
}

std::string Rectangle::Info()
{
    std::string info = "Rectangle(";
    info.append(std::to_string(length));
    info.append(", ");
    info.append(std::to_string(width));
    info.append(") [");
    info.append(std::to_string(GetArea()));
    info.append("]");
    return info;
}

Area_t Rectangle::GetArea()
{
    Area_t result = length * width;
    STATE::LOG(VLevel::Concise, std::string("The area of the `Rectangle` is ") + std::to_string(result) + ".");
    return result;
}

#endif