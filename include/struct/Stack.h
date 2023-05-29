#ifndef STACK_H
#define STACK_H

#include "../utility/ProgramState.h"
#include "../struct/StackException.h"

// == Declaration == //

template <typename T>
class Stack
{
private:
    unsigned int maxCapacity;
    unsigned int usedCapacity;
    T* stogagePtr;
    int topId;
public:
    Stack(unsigned int _maxCapacity = 8);
    ~Stack();
    
    std::string Info();
    void Push(T _value);
    void Pop();
    int Count() const;
    T Top() const;
    bool IsEmpty() const;
    bool IsFull() const;
};

// == Implementation == //

template <typename T>
Stack<T>::Stack(unsigned int _maxCapacity)
{
    maxCapacity = _maxCapacity;
    usedCapacity = 0;
    topId = -1;
    stogagePtr = new T[maxCapacity];
    STATE::LOG(VLevel::Detailed, "Constructed a `Stack` instance.");
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] stogagePtr;
    STATE::LOG(VLevel::Detailed, "Destroyed a `Stack` instance.");
}

template <typename T>
std::string Stack<T>::Info()
{
    std::string info = "Stack(";
    info.append(std::to_string(usedCapacity));
    info.append("/");
    info.append(std::to_string(maxCapacity));
    info.append(")");
    return info;
}

template <typename T>
void Stack<T>::Push(T _value)
{
    if (IsFull())
    {
        STATE::ERR("Failed to perform a `Push()` operation. (stask is full)");
        throw StackOverflow("stask is full");
    }
    stogagePtr[++topId] = _value;
    usedCapacity++;
    STATE::LOG(VLevel::Concise, "Successfully performed a `Push()` operation.");
}

template <typename T>
void Stack<T>::Pop()
{
    if (IsEmpty())
    {
        STATE::ERR("Failed to perform a `Pop()` operation. (stask is empty)");
        throw StackUnderflow("stask is empty");
    }
    topId--;
    usedCapacity--;
    STATE::LOG(VLevel::Concise, "Successfully performed a `Pop()` operation.");
}

template <typename T>
int Stack<T>::Count() const
{
    return usedCapacity;
}

template <typename T>
T Stack<T>::Top() const
{
    if (IsEmpty())
    {
        STATE::ERR("Failed to obtain the `Top()` object. (stask is empty)");
        throw StackUnderflow("stask is empty");
    }
    STATE::LOG(VLevel::Concise, "Successfully obtained the `Top()` object.");
    return stogagePtr[topId];
}

template <typename T>
bool Stack<T>::IsEmpty() const
{
    STATE::LOG(VLevel::Detailed, std::string("`IsEmpty()` is ") + ((usedCapacity == 0) ? "true." : "false."));
    return usedCapacity == 0;
}

template <typename T>
bool Stack<T>::IsFull() const
{
    STATE::LOG(VLevel::Detailed, std::string("`IsFull()` is ") + ((usedCapacity == maxCapacity) ? "true." : "false."));
    return usedCapacity == maxCapacity;
}

#endif