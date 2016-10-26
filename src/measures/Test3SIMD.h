#pragma once

#include "ITest.h"

namespace Test
{

    class Test3SIMD : public ITest
    {
    public:
        void virtual Run(std::size_t testRepetitions) override;
    };
}