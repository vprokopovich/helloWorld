#pragma once

#include <sstream>      // for std::stringstream
#include <string>

/*
* Prints elements of a container to std::out
*/
template<typename T>
std::string Print(std::vector<T> data)
{
    std::stringstream s;
    for (auto& item : data) s << item << std::string(", ");
    return s.str();
}

/*
* Compares 2 containers of the same type element-by-element
*/
template<typename TContainer>
bool Compare(const TContainer& in1, const TContainer& in2)
{
    if (in1.size() != in2.size())
    {
        return false;
    }

    for (auto it1 = in1.begin(), it2 = in2.begin(); it1 != in1.end(); it1++, it2++)
    {
        if (in1 != in2) return false;
    }

    return true;
}