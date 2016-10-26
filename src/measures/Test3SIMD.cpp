#include "Test3SIMD.h"

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

void Test3SIMD::Run(std::size_t testRepetitions)
{
    using ArgType = std::uint64_t;

    const std::size_t numberIterations = std::numeric_limits<std::uint32_t>::max() / 1024;
    const std::size_t valuesCount = std::numeric_limits<std::uint32_t>::max() / 1024;
    std::vector<ArgType> inputData(valuesCount);
    std::vector<ArgType> outputData1(valuesCount);
    std::vector<ArgType> outputData2(valuesCount);
    std::vector<ArgType> outputDataDebug(valuesCount);
    std::generate(inputData.begin(), inputData.end(), std::rand);

    {
        auto withoutSIMD = [&inputData, &outputData1, &valuesCount] (const ArgType& count) -> void
        {
            // Some code
            std::uint64_t counter = 0;
            for (std::size_t i = 1; i < (valuesCount - 2); ++i)
            {
                outputData1[i] = (inputData[i - 1] + inputData[i] + inputData[i + 1] + inputData[i + 2]) / 4;
            }
        };
        auto averageDuration = Util::Measure(withoutSIMD, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Processing without SIMD, ", numberIterations));
    }

    {
        auto withSIMD = [&inputData, &outputData2, &outputDataDebug, &valuesCount](const ArgType& count) -> void
        {
            // Some code
            std::uint16_t counter = 0;
            std::size_t   step = sizeof(__m128i) / sizeof(ArgType);

            for (std::size_t i = 1; i < (valuesCount - 2); i += step)
            {
                __m128i vectorizedInput1 = _mm_loadu_si128(reinterpret_cast<__m128i*>(&inputData[i - 1]));
                __m128i vectorizedInput2 = _mm_loadu_si128(reinterpret_cast<__m128i*>(&inputData[i]));
                __m128i vectorizedInput3 = _mm_loadu_si128(reinterpret_cast<__m128i*>(&inputData[i + 1]));
                __m128i vectorizedInput4 = _mm_loadu_si128(reinterpret_cast<__m128i*>(&inputData[i + 2]));
                __m128i vectorizedAvg1 = _mm_avg_epu16(vectorizedInput1, vectorizedInput2);
                __m128i vectorizedAvg2 = _mm_avg_epu16(vectorizedInput3, vectorizedInput4);
                __m128i output = _mm_avg_epu16(vectorizedAvg1, vectorizedAvg2);
                _mm_storeu_si128(reinterpret_cast<__m128i*>(&outputData2[i]), output);

                /*
                vectorizedInput2 = _mm_avg_epu16(vectorizedInput1, vectorizedInput2);
                vectorizedInput4 = _mm_avg_epu16(vectorizedInput3, vectorizedInput4);
                _mm_storeu_si128(reinterpret_cast<__m128i*>(&outputData2[i]), _mm_avg_epu16(vectorizedInput2, vectorizedInput4));
                */
            }
        };

        auto averageDuration = Util::Measure(withSIMD, numberIterations, testRepetitions);
        Util::Print(averageDuration, generateOutputString("Processing with SSE, ", numberIterations));
    }
}
