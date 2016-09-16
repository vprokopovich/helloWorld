#pragma once

#include "ITest.h"

namespace Test
{
    struct Number1
    {
        Number1()
            : _memberValue(0)
            , _someAdditionalData1(0)
        {
        }

        Number1& operator++ ()     // prefix ++
        {
            // Do work on this.   (increment your object here)
            ++_memberValue;
            return *this;
        }

        // You want to make the ++ operator work like the standard operators
        // The simple way to do this is to implement postfix in terms of prefix.
        Number1  operator++ (int)  // postfix ++
        {
            Number1 result(*this);   // make a copy for result
            ++(*this);              // Now use the prefix version to do the work
            return result;          // return the copy (the old) value.
        }

        std::uint64_t _memberValue;
        std::uint64_t _someAdditionalData1;
    };

    struct Number2
    {
        Number2()
            : _memberValue(0)
            , _someAdditionalData1(0)
            , _someAdditionalData2(0)
            , _someAdditionalData3(0)
            , _someAdditionalData4(0)
        {
        }

        inline Number2& operator++ ()     // prefix ++
        {
            // Do work on this.   (increment your object here)
            ++_memberValue;
            return *this;
        }

        // You want to make the ++ operator work like the standard operators
        // The simple way to do this is to implement postfix in terms of prefix.
        inline Number2  operator++ (int)  // postfix ++
        {
            Number2 result(*this);   // make a copy for result
            ++(*this);              // Now use the prefix version to do the work
            return result;          // return the copy (the old) value.
        }

        std::uint64_t _memberValue;
        std::uint64_t _someAdditionalData1;
        std::uint64_t _someAdditionalData2;
        std::uint64_t _someAdditionalData3;
        std::uint64_t _someAdditionalData4;
    };

    class Test1PrefixPostfix : public ITest
    {
    public:
        void virtual Run(std::size_t testRepetitions) override;
    };
}