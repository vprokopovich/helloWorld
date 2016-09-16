#pragma once

#include <measurements.h>
#include <iostream>
#include <string>

namespace Util
{
    void Print(const TTimeType& duration, const std::string& testName)
    {
        using namespace std::chrono;
#ifdef OPTIMIZATION_FLAG
        std::cout << "Optimization: " << OPTIMIZATION_FLAG << " ; ";
#endif
        std::cout << testName << "; " << duration_cast<milliseconds>(duration).count() << " ; ms" << std::endl;
    }
}