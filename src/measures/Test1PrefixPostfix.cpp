#include "Test1PrefixPostfix.h"

#include <sstream>
#include <limits>
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

void Test1PrefixPostfix::Run(std::size_t testRepetitions)
{
    using ArgType = std::uint64_t;
    const ArgType numberIterations = std::numeric_limits<std::uint32_t>::max() / 16;

    {
        auto prefixIncrement = [](const ArgType& count) -> void
        {
            std::uint64_t counter = 0;
            for (auto i = 0; i < count; ++i)
            {
                ++counter;
            }
        };
        auto averageDuration = Util::Measure(prefixIncrement, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Prefix increment of one value, simple type,", numberIterations));
    }
    {
        auto postfixIncrement = [](const ArgType& count) -> void
        {
            std::uint64_t counter = 0;
            for (auto i = 0; i < count; ++i)
            {
                counter++;
            }
        };
        auto averageDuration = Util::Measure(postfixIncrement, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Postfix increment of one value, simple type,", numberIterations));
    }
    {
        auto prefixIncrementComplexType = [](const ArgType& count) -> void
        {
            Number1 counter;
            for (auto i = 0; i < count; ++i)
            {
                ++counter;
            }
        };
        auto averageDuration = Util::Measure(prefixIncrementComplexType, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Prefix increment of one value, complex type 2*64bits,", numberIterations));
    }
    {
        auto postfixIncrementComplexType = [](const ArgType& count) -> void
        {
            Number1 counter;
            for (auto i = 0; i < count; ++i)
            {
                counter++;
            }
        };
        auto averageDuration = Util::Measure(postfixIncrementComplexType, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Postfix increment of one value, complex type 2*64bits,", numberIterations));
    }
    {
        auto prefixIncrementComplexType = [](const ArgType& count) -> void
        {
            Number2 counter;
            for (auto i = 0; i < count; ++i)
            {
                ++counter;
            }
        };
        auto averageDuration = Util::Measure(prefixIncrementComplexType, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Prefix increment of one value, complex type 4*64bits,", numberIterations));
    }
    {
        auto postfixIncrementComplexType = [](const ArgType& count) -> void
        {
            Number2 counter;
            for (auto i = 0; i < count; ++i)
            {
                counter++;
            }
        };
        auto averageDuration = Util::Measure(postfixIncrementComplexType, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Postfix increment of one value, complex type 4*64bits,", numberIterations));
    }
}
