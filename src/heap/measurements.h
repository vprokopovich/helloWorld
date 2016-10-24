#pragma once

#include <chrono>
#include <stdint.h>

namespace Util
{
    using TTimeType = std::chrono::duration<std::chrono::high_resolution_clock::rep, std::chrono::high_resolution_clock::period>;

    template <typename T, typename F>
    static TTimeType Measure(F f, T& inputData, std::size_t count = 100)
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

    //  Windows
    // RDTSC - Read Time Stamp Counter
    #ifdef _WIN32
        #include <intrin.h>
        static std::uint64_t ReadTimestampCounter()
        {
            return __rdtsc();
        }
    //  Linux/GCC
    #else
        static std::uint64_t ReadTimestampCounter()
        {
            unsigned int lo, hi;
            __asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
            return ((uint64_t)hi << 32) | lo;
        }
    #endif
}