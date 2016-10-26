#pragma once

#include "ITest.h"

namespace Test
{

    class Test2TryCatch : public ITest
    {
    public:
        void virtual Run(std::size_t testRepetitions) override;
    };
}