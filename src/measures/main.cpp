#include "Test1PrefixPostfix.h"
#include "Test2TryCatch.h"
#include "Test3SIMD.h"
#include "Test4CycleOptimizations.h"
#include "Test5BranchPrediction.h"

const std::size_t TEST_REPETITIONS = 10;

int main()
{
    /*
    Test::Test1PrefixPostfix t1;
    t1.Run(TEST_REPETITIONS);

    Test::Test2TryCatch t2;
    t2.Run(TEST_REPETITIONS);

    Test::Test3SIMD t3;
    t3.Run(TEST_REPETITIONS);
    */
    Test::Test4CycleOptimizations t4;
    t4.Run(TEST_REPETITIONS);

    Test::Test5BranchPrediction t5;
    t5.Run(TEST_REPETITIONS);

    return 0;
}