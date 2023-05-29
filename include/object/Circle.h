#ifndef CIRCLE_H
#define CIRCLE_H

#include "../utility/LynType.h"
#include "../object/Shape.h"
#include "../utility/ProgramState.h"

// == Declaration == //

const double PI = 3.1415926;

class Circle : public Shape
{
private:
    Length_t radius;
public:
    Circle(Length_t _radius);
    
    std::string Info() override;
    Area_t GetArea() override;
};

// == Implementation == //

Circle::Circle(Length_t _radius)
{
    if (_radius <= 0)
    {
        throw std::invalid_argument("length not larger than 0");
    }
    radius = _radius;
    STATE::LOG(VLevel::Detailed, "Manually constructed a `Circle` instance.");
}

std::string Circle::Info()
{
    std::string info = "Circle(";
    info.append(std::to_string(radius));
    info.append(") [");
    info.append(std::to_string(GetArea()));
    info.append("]");
    return info;
}

Area_t Circle::GetArea()
{
    Area_t result = PI * radius * radius;
    STATE::LOG(VLevel::Concise, std::string("The area of the `Circle` is ") + std::to_string(result) + ".");
    return result;
}

#endif