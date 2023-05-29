#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>
#include "../utility/LynType.h"
#include "../object/Shape.h"
#include "../utility/ProgramState.h"

// == Declaration == //

class Triangle : public Shape
{
private:
    Length_t a;
    Length_t b;
    Length_t c;
public:
    Triangle(Length_t _a, Length_t _b, Length_t _c);
    
    std::string Info() override;
    Area_t GetArea() override;
};

// == Implementation == //

Triangle::Triangle(Length_t _a, Length_t _b, Length_t _c)
{
    if (_a <= 0 || _b <= 0 || _c <= 0)
    {
        throw std::invalid_argument("length not larger than 0");
    }
    if (_a + _b <= _c || _a + _c <= _b || _b + _c <= _a)
    {
        throw std::invalid_argument("provided argument cannot form a triangle");
    }
    a = _a;
    b = _b;
    c = _c;
    STATE::LOG(VLevel::Detailed, "Manually constructed a `Triangle` instance.");
}

std::string Triangle::Info()
{
    std::string info = "Triangle(";
    info.append(std::to_string(a));
    info.append(", ");
    info.append(std::to_string(b));
    info.append(", ");
    info.append(std::to_string(c));
    info.append(") [");
    info.append(std::to_string(GetArea()));
    info.append("]");
    return info;
}

Area_t Triangle::GetArea()
{
    Area_t s = (a + b + c) / 2.0;
    Area_t result = std::sqrt(s * (s - a) * (s - b) * (s - c));
    STATE::LOG(VLevel::Concise, std::string("The area of the `Triangle` is ") + std::to_string(result) + ".");
    return result;
}

#endif