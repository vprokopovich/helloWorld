#include <iostream>     // for std::cout
#include <cinttypes>    // for type definitions
#include <vector>

#include "helpers.h"
#include "heap.h"
#include "sort.h"

void TestHeap()
{
    using Type = std::int32_t;
    using namespace Alg;    // For MyHeap, StdHeap

    const std::vector<Type> sourceData{ 1, 3, 5, 7, 10, 0, 45, 9, 11 };
    //std::cout << "Source array:   " << Util::ToString(sourceData) << std::endl;

    // Creating heaps
    MyHeap<Type> myHeap(sourceData);
    //MyHeap<Type> myHeap{ 1, 3, 5, 7, 10, 0, 45, 9, 11 }; // another possibility
    StdHeap<Type> stdHeap(sourceData);

    //std::cout << "Heap internals: " << Util::ToString(myHeap.GetRaw()) << std::endl;

    // Checking push to heap
    {
        myHeap.Push(100);
        stdHeap.Push(100);
        myHeap.Push(99);
        stdHeap.Push(99);

        //std::cout << "Heap internals after pushing values: " << Util::ToString(myHeap.GetRaw()) << std::endl;
        Util::CheckEqual(myHeap.GetRaw(), stdHeap.GetRaw(), __FILE__, __LINE__);
    }

    // Checking pop from heap
    {
        myHeap.Pop(); // getting 100
        stdHeap.Pop();

        myHeap.Pop(); // getting  99
        stdHeap.Pop();

        const auto heapSize = myHeap.GetSize();
        for (auto i = 0; i < heapSize; i++)
        {
            auto val1 = myHeap.Pop();
            auto val2 = stdHeap.Pop();
            Util::CheckEqual(val1, val2, __FILE__, __LINE__);
        }

        Util::CheckTrue(myHeap.GetSize() == 0, __FILE__, __LINE__);
        Util::CheckTrue(stdHeap.GetSize() == 0, __FILE__, __LINE__);
    }

    // Checking that exceptions are thrown when heap is empty
    {
        bool gotEx1 = false;
        try
        {
            myHeap.Pop();
        }
        catch (std::out_of_range& ex)
        {
            gotEx1 = true;
        }

        bool gotEx2 = false;
        try
        {
            stdHeap.Pop();
        }
        catch (std::out_of_range& ex)
        {
            gotEx2 = true;
        }
        Util::CheckTrue(gotEx1, __FILE__, __LINE__);
        Util::CheckTrue(gotEx2, __FILE__, __LINE__);
    }
}

void TestBubbleSort()
{
    using Type = std::int32_t;
    using namespace Alg;    // For BubbleSort

    const std::vector<Type> sourceData{ 1, 3, 5, 7, 10, 0, 45, 9, 11, 345, 101 };
    std::cout << "Source: " << Util::ToString(sourceData) << std::endl;

    BubbleSort<std::vector<Type>> sorter;
    auto data1(sourceData);
    sorter.Sort(data1);


    std::cout << "Sorted: " << Util::ToString(data1) << std::endl;
}

int main(int argc, char** argv)
{
    TestHeap();
    TestBubbleSort();

    return 0;
}