#pragma once

#include "ITest.h"

namespace Test
{
    class TestZCycleOptimizations : public ITest
    {
    public:
        void virtual Run(std::size_t testRepetitions) override;
    };
}