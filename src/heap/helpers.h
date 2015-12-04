#pragma once

#include <sstream>      // for std::stringstream
#include <string>

namespace Util
{
    /*
    * Prints elements of a container to std::out
    */
    template<typename TContainer>
    std::string ToString(const TContainer& data)
    {
        std::stringstream s;
        for (auto& item : data) s << item << std::string(", ");
        return s.str();
    }

    /*
    * Compares 2 containers of the same type element-by-element
    */
    template<typename T, typename TContainer>
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

    /*
    * Compares 2 values the same type by value
    */
    template<typename TVal>
    bool Compare(const TVal& in1, const TVal& in2)
    {
        return (in1 == in2);
    }

    /*
    * Compares 2 values of the same type (containers or values),
    * checks for equality and prints error messages in case they are not equal
    *
    * @param in1    Operand1
    * @param in2    Operand2
    * @param pFile  (optional) string that represents position of the call in the file
    * @param line   (optional) number represents line of the call in file
    */
    template<typename T>
    void CheckEqual(const T& in1, const T& in2, const char* pFile = nullptr, int line = 0)
    {
        if (!Compare(in1, in2))
        {
            if (pFile && line)
            {
                std::cout << pFile << ":" << line << " ";
            }
            std::cout << "Fail" << std::endl;
        }
    }

    /*
    * Prints error message in case statement is false
    *
    * @param val    Operand1
    * @param pFile  (optional) string that represents position of the call in the file
    * @param line   (optional) number represents line of the call in file
    */
    void CheckTrue(bool val, const char* pFile = nullptr, int line = 0)
    {
        if (!val)
        {
            if (pFile && line)
            {
                std::cout << pFile << ":" << line << " ";
            }
            std::cout << "Fail" << std::endl;
        }
    }
}