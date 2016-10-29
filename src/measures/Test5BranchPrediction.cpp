#include "Test5BranchPrediction.h"

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

void Test5BranchPrediction::Run(std::size_t testRepetitions)
{
    using ArgType = std::uint64_t;

    const std::size_t numberIterations = std::numeric_limits<std::uint32_t>::max() / (1024);
    const std::size_t valuesCount = std::numeric_limits<std::uint32_t>::max() / 1024;
    std::vector<ArgType> inputData(valuesCount);
    std::generate(inputData.begin(), inputData.end(), std::rand);

    {
        bool isTrue = true;
        auto test = [&inputData, &valuesCount, &isTrue] (const ArgType& count) -> void
        {
            // Some code
            std::uint64_t counter = 0;

            if (isTrue)
            {
                for (auto i = 0; i < count; ++i)
                {
                    counter++;
                }
            }
            else
            {
                for (auto i = 0; i < count; ++i)
                {
                    counter++;
                }
            }
        };
        auto averageDuration1 = Util::Measure(test, numberIterations, testRepetitions);
        Util::Print(averageDuration1, generateOutputString("'Right' branch of if, ", numberIterations));

        isTrue = false;
        auto averageDuration2 = Util::Measure(test, numberIterations, testRepetitions);
        Util::Print(averageDuration2, generateOutputString("'Wrong' branch of if, ", numberIterations));
    }
}
