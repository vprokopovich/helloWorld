#include "Test2TryCatch.h"

//#include <string>
#include <sstream>
#include <exception>
//#include <limits>
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
struct SomeException : public std::exception
{
};

void SomeFunctionWithException(bool throwException)
{
    if (throwException)
    {
        throw SomeException();
    }
}
void SomeFunctionWithoutException()
{
    ;
}

void Test2TryCatch::Run(std::size_t testRepetitions)
{
    using ArgType = std::uint64_t;
    const ArgType numberIterations = std::numeric_limits<std::uint32_t>::max() / 1024;

    {
        auto withoutThrowBlock = [](const ArgType& count) -> void
        {
            // Some code
            std::uint64_t counter = 0;
            for (auto i = 0; i < count; ++i)
            {
                SomeFunctionWithoutException();
            }
        };
        auto averageDuration = Util::Measure(withoutThrowBlock, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Some code without throw block at all, ", numberIterations));
    }

    {
        auto withThrowBlockNoThrow = [](const ArgType& count) -> void
        {
            // Some code
            std::uint64_t counter = 0;
            for (auto i = 0; i < count; ++i)
            {
                try
                {
                    SomeFunctionWithException(false);  // Do not throw an exception
                }
                catch (std::exception& ex)
                {
                    ;
                }
            }
        };
        auto averageDuration = Util::Measure(withThrowBlockNoThrow, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Some code with throw block, but no throw occured, ", numberIterations));
    }

    {
        auto withThrowBlock = [](const ArgType& count) -> void
        {
            // Some code
            std::uint64_t counter = 0;
            for (auto i = 0; i < count; ++i)
            {
                try
                {
                    SomeFunctionWithException(true);  // Throw an exception
                }
                catch (std::exception& ex)
                {
                    ;
                }
            }
        };
        auto averageDuration = Util::Measure(withThrowBlock, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Some code with throw block, ", numberIterations));
    }
}
