#pragma once

#include <sstream>      // for std::stringstream
#include <string>
#include <random>

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
    * Generate vector of random values
    * Please note, possible types are: signed/unsigned integers, floating points
    * You`ll get compile time error in case if type T is not any of listed above (bool, char, classes, etc)
    * due to implementation of std::uniform_real_distribution, std::uniform_int_distribution
    *
    * @param count  Number of values to be generated
    * @param min    Minimal value
    * @param max    Maximal value
    * @return vector with random values in specified range of specified type
    */
    template<typename T>
    std::vector<T> GetRandomVector(const std::size_t count, const T min = 0, const T max = 1000)
    {
        std::random_device rd;
        std::mt19937 mt(rd());

        // Deducing type at compile time
        typename std::conditional<std::is_floating_point<T>::value,   // if T is a floating point type
                                  std::uniform_real_distribution<T>,  // then selecting type std::uniform_real_distribution<T>
                                  std::uniform_int_distribution<T>>   // else selecting type std::uniform_int_distribution<T>
            ::type dist(min, max);                                    // Defining variable of selected type

        std::vector<T> retVal(count);
        for (std::size_t i = 0; i < count; i++)
        {
            retVal[i] = dist(mt);
        }
        return retVal;
    }

    /*
    * Prints error message in case statement is false
    *
    * @param val    Operand1
    * @param pFile  (optional) string that represents position of the call in the file
    * @param line   (optional) number represents line of the call in file
    */
    static
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

    static
    void CheckFalse(bool val, const char* pFile = nullptr, int line = 0)
    {
        CheckTrue(!val, pFile, line);
    }

    template<typename T>
    bool IsSorted(const T& container)
    {
        typename T::value_type value = container.front();
        for (auto& v : container)
        {
            if (v < value)
            {
                return false;
            }
            value = v;
        }

        return true;
    }
}