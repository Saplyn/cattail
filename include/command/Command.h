#ifndef COMMAND_H
#define COMMAND_H

#include "../object/Shape.h"
#include "../object/Circle.h"
#include "../object/Triangle.h"
#include "../object/Rectangle.h"

#include "../struct/Stack.h"

#include "../command/Message.h"

#include "../utility/ValidString.h"

#include <sstream>
#include <map>

// == Declaration == //

namespace CMD
{
    std::stringstream lync;
    Circle* circPtr;
    Triangle* triaPtr;
    Rectangle* rectPtr;
    enum ptrType { none, circ, tria, rect } tmpType;
    Stack<Shape*> stack;
    std::map<int, Area_t> areaMap;
    
    void Info();
    void Help();
    namespace SET
    {
        void Help();
        void Verbose();
        void Color();
    }
    namespace NEW
    {
        void Help();
        void Circ();
        void Rect();
        void Tria();
    }
    void DeleteFor(ptrType ptype);
    void Tmp();
    namespace STK
    {
        void Help();
        void Push();
        void Pop();
        void Top();
        void State();
    }
    void Exit();
}

// == Implementation == //

void CMD::Info() { std::cout << INFO_MSG << std::endl; }
void CMD::Help() { std::cout << HELP_MSG << std::endl; }
void CMD::SET::Help() { std::cout << SET_HELP_MSG << std::endl; }
void CMD::SET::Verbose()
{
    std::string vlvl;
    lync >> vlvl;
    STATE::LOG(VLevel::Detailed, "`Verbose()` recieved \"" + vlvl + "\" from `lync`.");
    if (vlvl == "silent") { STATE::SetVerbose(VLevel::Silent); }
    else if (vlvl == "report") { STATE::SetVerbose(VLevel::Report); }
    else if (vlvl == "concise") { STATE::SetVerbose(VLevel::Concise); }
    else if (vlvl == "detailed") { STATE::SetVerbose(VLevel::Detailed); }
    else
    {
        STATE::ALR("Invalid argument: \"" + vlvl + "\"");
        std::cout << SET_VERBOSE_HELP_MSG << std::endl;
    }
}
void CMD::SET::Color()
{
    std::string value;
    lync >> value;
    STATE::LOG(VLevel::Detailed, "`Color()` recieved \"" + value + "\" from `lync`.");
    if (value == "true") { STATE::SetColor(true); }
    else if (value == "false") { STATE::SetColor(false); }
    else
    {
        STATE::ALR("Invalid argument: \"" + value + "\"");
        std::cout << SET_COLOR_HELP_MSG << std::endl;
    }
}
void CMD::NEW::Help() { std::cout << NEW_HELP_MSG << std::endl; }
void CMD::NEW::Circ()
{
    if (VS::IsNumberSequence(lync.str()) < 1)
    {
        STATE::ALR("Invalid argument.");
        CMD::NEW::Help();
        return;
    }
    Length_t r;
    lync >> r;
    STATE::LOG(VLevel::Detailed, "`Circ()` recieved \"" + std::to_string(r) + "\" from `lync`.");
    DeleteFor(ptrType::circ);
    circPtr = new Circle(r);
}
void CMD::NEW::Rect()
{
    if (VS::IsNumberSequence(lync.str()) < 2)
    {
        STATE::ALR("Invalid argument.");
        CMD::NEW::Help();
        return;
    }
    Length_t l, w;
    lync >> l >> w;
    STATE::LOG(VLevel::Detailed, "`Circ()` recieved \"" + std::to_string(l) + ", " + std::to_string(w) + "\" from `lync`.");
    DeleteFor(ptrType::rect);
    rectPtr = new Rectangle(l, w);
}
void CMD::NEW::Tria()
{
    if (VS::IsNumberSequence(lync.str()) < 3)
    {
        STATE::ALR("Invalid argument.");
        CMD::NEW::Help();
        return;
    }
    Length_t a, b, c;
    lync >> a >> b >> c;
    STATE::LOG(VLevel::Detailed, "`Circ()` recieved \"" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + "\" from `lync`.");
    DeleteFor(ptrType::tria);
    triaPtr = new Triangle(a, b, c);
}
void CMD::DeleteFor(ptrType ptype)
{
    switch (tmpType)
    {
        case ptrType::none: break;
        case ptrType::circ: delete circPtr; break;
        case ptrType::tria: delete triaPtr; break;
        case ptrType::rect: delete rectPtr; break;
    }
    tmpType = ptype;
}
void CMD::Tmp()
{
    switch (tmpType)
    {
        case ptrType::none: std::cout << "Nothing stored in temporary memory." << std::endl; break;
        case ptrType::circ: std::cout << circPtr->Info() << std::endl; break;
        case ptrType::tria: std::cout << triaPtr->Info() << std::endl; break;
        case ptrType::rect: std::cout << rectPtr->Info() << std::endl; break;
    }
}
void CMD::STK::Help() { std::cout << STK_HELP_MSG << std::endl; }
void CMD::STK::Push()
{
    switch (tmpType)
    {
        case ptrType::none:
            STATE::ALR("Nothing stored in temporary memory, push operation terminated.");
            return;
        case ptrType::circ: stack.Push(circPtr); break;
        case ptrType::tria: stack.Push(triaPtr); break;
        case ptrType::rect: stack.Push(rectPtr); break;
    }
    tmpType = ptrType::none;
    areaMap[stack.Count()] = stack.Top()->GetArea();
}
void CMD::STK::Pop()
{
    areaMap.erase(stack.Count());
    try { delete stack.Top(); } catch (...) {}
    stack.Pop();
}
void CMD::STK::Top() { std::cout << stack.Top()->Info() << std::endl; }
void CMD::STK::State() { std::cout << stack.Info() << std::endl; }
void CMD::Exit()
{
    std::cout << EXIT_MSG << std::endl;
    exit(0);
}

#endif

/*

[command]
=value

[cattail]
├── [set]
│   ├── [help]
│   ├── [verbose]
│   │   ├── =silent
│   │   ├── =report
│   │   ├── =concise
│   │   └── =detailed
│   └── [color]
│       ├── =true
│       └── =false
├── [new]
│   ├── [help]
│   ├── [shape]
│   ├── [circle]
│   │   └── =r
│   ├── [rectangle]
│   │   └── =l,w
│   └── [triangle]
│       └── =a,b,c
├── [tmp]
└── [stk]
    ├── [help]
    ├── [push]
    ├── [pop]
    ├── [top]
    └── [state]

*/