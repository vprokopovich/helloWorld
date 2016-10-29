#pragma once

#include "ITest.h"

namespace Test
{

    class Test5BranchPrediction : public ITest
    {
    public:
        void virtual Run(std::size_t testRepetitions) override;
    };
}