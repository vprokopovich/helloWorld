#pragma once

#include <cstddef>
#include <cstdint>

namespace Test
{
    class ITest
    {
    public:
        void virtual Run(std::size_t testRepetitions) = 0;
        virtual ~ITest() {}
    };
}