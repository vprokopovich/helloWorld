#include "TestZCycleOptimizations.h"

#include <string>
#include <measurements.h>
#include "logging.h"

using namespace Test;

namespace
{
    typedef struct
    {
        long len;
        float *data;
    } vec;

    long vec_len(vec *v)
    {
        return v->len;
    }

    std::uint64_t combine0(vec *v, float *dest)
    {
        long i;
        *dest = 1;
        auto start = Util::ReadTimestampCounter();
        for (i = 0; i < vec_len(v); i++)
        {
            *dest *= v->data[i];
        }
        auto end = Util::ReadTimestampCounter();

        return end - start;
    }

    std::uint64_t combineOptimized(vec *v, float *dest)
    {
        auto start = Util::ReadTimestampCounter();

        long i;
        *dest = 1;
        float acc = 1;
        
        const auto len = vec_len(v);
        for (i = 0; i < len; i++)
        {
            acc *= v->data[i];
        }
        *dest = acc;

        auto end = Util::ReadTimestampCounter();
        return end - start;
    }

    const std::size_t SIZE = 5000;
    float a[SIZE];
    vec v = { SIZE, a };
}

void Test::TestZCycleOptimizations::Run(std::size_t testRepetitions)
{
    float res;
    for (auto i = 0; i < SIZE; i++)
    {
        a[i] = rand();
    }

    auto measure1 = combine0(&v, &res);
    auto measure2 = combineOptimized(&v, &res);

    std::cout << "Per value non-optimized: " << measure1 / SIZE << std::endl;
    std::cout << "Per value optimized: " << measure2 / SIZE << std::endl;
}