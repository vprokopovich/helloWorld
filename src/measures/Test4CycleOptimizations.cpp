#include "Test4CycleOptimizations.h"

#include <sstream>
#include <vector>
#include <algorithm>
#include <emmintrin.h>
#include <measurements.h>
#include "logging.h"

using namespace Test;

namespace
{
    std::string generateOutputString(const std::string& text, const std::uint64_t iterations)
    {
        std::stringstream s;
        s << text << iterations << " times";
        return s.str();
    };
}

void Test4CycleOptimizations::Run(std::size_t testRepetitions)
{
    using ArgType = std::uint64_t;

    const std::size_t numberIterations = std::numeric_limits<std::uint32_t>::max() / (1024);
    const std::size_t valuesCount =  std::numeric_limits<std::uint32_t>::max() / 512 + 1;
    std::vector<ArgType> inputData(valuesCount);
    std::generate(inputData.begin(), inputData.end(), std::rand);

    {
        auto test = [&inputData, &valuesCount] (const ArgType& count) -> void
        {
            ArgType res = 0;
            for (std::size_t i = 0; i < valuesCount; i++)
            {
                res *= inputData[i];
            }
            std::cout << "Res1" << res << std::endl;
        };

        auto averageDuration = Util::Measure(test, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Cycle, ", numberIterations));
    }
    {
        auto testUnfolded1 = [&inputData, &valuesCount](const ArgType& count) -> void
        {
            ArgType res = 0;
            ArgType* pInputData = &inputData[0];
            for (std::size_t i = 0; i < valuesCount; i += 4)
            {
                /*
                res *= *pInputData++;
                res *= *pInputData++;
                res *= *pInputData++;
                res *= *pInputData++;
                */
                res *= inputData[i];
                res *= inputData[i + 1];
                res *= inputData[i + 2];
                res *= inputData[i + 3];
            }
            std::cout << "Res2" << res << std::endl;
        };

        auto averageDuration = Util::Measure(testUnfolded1, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Unfolded cycle #1, ", numberIterations));
    }
    {
        auto testUnfolded2 = [&inputData, &valuesCount](const ArgType& count) -> void
        {
            ArgType res1 = 0;
            ArgType res2 = 0;
            ArgType res3 = 0;
            ArgType res4 = 0;
            for (std::size_t i = 0; i < valuesCount; i += 4)
            {
                res1 *= inputData[i];
                res2 *= inputData[i + 1];
                res3 *= inputData[i + 2];
                res4 *= inputData[i + 3];
            }
            ArgType res = res1 * res2 * res3 * res4;
            std::cout << "Res3" << res << std::endl;
        };

        auto averageDuration = Util::Measure(testUnfolded2, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Unfolded cycle #2, ", numberIterations));
    }
}
