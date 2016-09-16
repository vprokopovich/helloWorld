#include <chrono>

namespace Util
{
    template <typename T, typename F>
    std::chrono::duration<std::chrono::high_resolution_clock::rep, std::chrono::high_resolution_clock::period>
    Measure(F f, T& inputData, std::size_t count = 100)
    {
        std::chrono::duration<std::chrono::high_resolution_clock::rep,
                              std::chrono::high_resolution_clock::period> retVal(0);
        for (std::size_t i = 0; i < count; i++)
        {
            auto dataToProcess = inputData;
            auto begin = std::chrono::high_resolution_clock::now();

            f(dataToProcess);

            auto end = std::chrono::high_resolution_clock::now();
            retVal += end - begin;
        }

        return retVal / count;
    }
}