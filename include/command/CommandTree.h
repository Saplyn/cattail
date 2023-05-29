#ifndef COMMAND_TREE_H
#define COMMAND_TREE_H

#include "../utility/ProgramState.h"
#include <vector>
#include <string>
#include <functional>

// == Declaration == //

class CTree
{
private:
    std::function<void()> function;
    std::string pattern;
    std::string description;
    std::vector<CTree*> children;
public:
    CTree(std::string _pattern, std::function<void()> _func);
    CTree(std::string _pattern, std::function<void()> _func, std::string _dscp);
    
    void Grow(CTree* _child);
    std::function<void()> Retrieve(std::vector<std::string> _patterns);
    std::function<void()> Retrieve(std::vector<std::string> _patterns, int& _pos);
    static void CommandSlice(std::string _input, std::vector<std::string>& _cmd);
};

// == Implementation == //

// Comnstruct a Command Tree
CTree::CTree(std::string _pattern, std::function<void()> _func)
{
    function = _func;
    pattern = _pattern;
    STATE::LOG(VLevel::Detailed, "Constructed a `CTree` object with pattern \"" + pattern + "\" and assigned a function.");
}

// Comnstruct a Command Tree with description
CTree::CTree(std::string _pattern, std::function<void()> _func, std::string _dscp)
{
    function = _func;
    pattern = _pattern;
    description = _dscp;
    STATE::LOG(VLevel::Detailed, "Constructed a `CTree` object with pattern \"" + pattern + "\" and assigned a function.");
}

// Grow a child Command Tree
void CTree::Grow(CTree* _child)
{
    children.push_back(_child);
    STATE::LOG(VLevel::Detailed, "`CTree` object \"" + pattern + "\" now has a child with pattern \"" + _child->pattern + "\".");
}

// Interpret command vector, retrive function to be executed
std::function<void()> CTree::Retrieve(std::vector<std::string> _patterns)
{
    CTree* current = this;
    bool found = false;
    
    STATE::LOG(VLevel::Detailed, "`Retrieve()` interpretion starts at \"" + pattern + "\"");
    for (int i = 0; i < _patterns.size(); i++)
    {
        found = false;
        for (auto child : current->children)
        {
            if (child->pattern == _patterns[i])
            {
                found = true;
                current = child;
                break;
            }
        }
        
        STATE::LOG(VLevel::Detailed, found ? "`Retrieve()` interpretion shifts to \"" + current->pattern + "\"."
                                           : "`Retrieve()` interpretion ends at \"" + current->pattern + "\".");
        if (!found) { break; }
    }
    
    STATE::LOG(VLevel::Concise, "Command interpreted into operation \"" + current->description + "\".");
    return current->function;
}

// Interpret command vector, retrive function to be executed, get stopped position
std::function<void()> CTree::Retrieve(std::vector<std::string> _patterns, int& _pos)
{
    CTree* current = this;
    bool found = false;
    
    STATE::LOG(VLevel::Detailed, "`Retrieve()` interpretion starts at \"" + pattern + "\"");
    for (_pos = 0; _pos < _patterns.size(); _pos++)
    {
        found = false;
        for (auto child : current->children)
        {
            if (child->pattern == _patterns[_pos])
            {
                found = true;
                current = child;
                break;
            }
        }
        
        STATE::LOG(VLevel::Detailed, found ? "`Retrieve()` interpretion shifts to \"" + current->pattern + "\"."
                                           : "`Retrieve()` interpretion ends at \"" + current->pattern + "\".");
        if (!found) { break; }
    }
    
    STATE::LOG(VLevel::Concise, "Command interpreted into operation \"" + current->description + "\".");
    return current->function;
}

// Slice the command string into a vector that Command Tree can interpret
void CTree::CommandSlice(std::string _input, std::vector<std::string>& _cmd)
{
    _cmd.clear();
    size_t pos = 0;
    while ((pos = _input.find(' ')) != std::string::npos)
    {
        _cmd.push_back(_input.substr(0, pos));
        _input.erase(0, pos + 1);
    }
    _cmd.push_back(_input);
}

#endif