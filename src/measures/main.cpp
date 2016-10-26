#include "Test1PrefixPostfix.h"
#include "Test2TryCatch.h"
#include "Test3SIMD.h"
//#include "TestZCycleOptimizations.h"

const std::size_t TEST_REPETITIONS = 10;

int main()
{
    Test::Test1PrefixPostfix t1;
    t1.Run(TEST_REPETITIONS);

    Test::Test2TryCatch t2;
    t2.Run(TEST_REPETITIONS);

    Test::Test3SIMD t3;
    t3.Run(TEST_REPETITIONS);

    //Test::TestZCycleOptimizations tz;
    //tz.Run(TEST_REPETITIONS);

    return 0;
}