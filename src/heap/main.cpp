#include <iostream>     // for std::cout
#include <cinttypes>    // for type definitions
#include <vector>
#include <list>
#include <memory>
#include <chrono>
#include <functional>

#include "helpers.h"
#include "heap.h"
#include "sort.h"
#include "brackets.h"
#include "streamTest.h"

void TestHeap()
{
    using Type = std::int32_t;
    using namespace Alg;    // For MyHeap, StdHeap

    std::vector<Type> sourceData = Util::GetRandomVector<Type>(20);

    // Creating heaps
    MyHeap<Type> myHeap(sourceData);
    StdHeap<Type> stdHeap(sourceData);

    // Checking push to heap
    {
        myHeap.Push(100);
        stdHeap.Push(100);
        myHeap.Push(99);
        stdHeap.Push(99);

        // dumping graph to file
        /*
        auto handle = fopen("graph.dot", "a");
        auto myDot = DumpHeapToDot(myHeap, "MyHeap");
        auto stdDot = DumpHeapToDot(stdHeap, "StdHeap");
        fprintf(handle, "%s", myDot.c_str());
        fprintf(handle, "%s", stdDot.c_str());
        fclose(handle);
        std::cout << "Heap MY  internals after pushing values: " << Util::ToString(myHeap.GetRaw()) << std::endl;
        std::cout << "Heap STD internals after pushing values: " << Util::ToString(stdHeap.GetRaw()) << std::endl;
        */

        // TODO: implement another check. Under different compilers results may vary
        // Util::CheckEqual(myHeap.GetRaw(), stdHeap.GetRaw(), __FILE__, __LINE__);
    }

    // Checking pop from heap
    {
        const auto heapSize = myHeap.GetSize();
        for (std::size_t i = 0; i < heapSize; i++)
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
        catch (std::out_of_range& /*ex*/)
        {
            gotEx1 = true;
        }

        bool gotEx2 = false;
        try
        {
            stdHeap.Pop();
        }
        catch (std::out_of_range& /*ex*/)
        {
            gotEx2 = true;
        }
        Util::CheckTrue(gotEx1, __FILE__, __LINE__);
        Util::CheckTrue(gotEx2, __FILE__, __LINE__);
    }
}


void TestMergeSort()
{
    using Type = std::int32_t;
    using namespace Alg;    // For BubbleSort

    //const std::vector<Type> sourceData{ 1, 3, 5, 7, 10, 0, 45, 9, 11, 345, 101 };
    const std::list<Type> sourceData{ 1, 2, 5, 0, 9,14, 1, 3, 4 };
    //auto sourceData = Util::GetRandomVector<Type>(20);
    std::cout << "Source: " << Util::ToString(sourceData) << std::endl;

    MergeSort<std::list<Type>> sorter;
    auto data1(sourceData);
    sorter.Sort(data1);

    std::cout << "Sorted: " << Util::ToString(data1) << std::endl;

    Util::CheckTrue(Util::IsSorted(data1), __FILE__, __LINE__);
}

template <typename T, typename F>
std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>
MeasureSmth(F f/*std::function<void(std::vector<T>&)> f*/, T& inputData, std::size_t count = 100)
{
    std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> retVal;
    for (std::size_t i = 0; i < count; i++)
    {
        auto dataToProcess = inputData;
        auto begin = std::chrono::high_resolution_clock::now();
        f(dataToProcess);
        auto end = std::chrono::high_resolution_clock::now();

        retVal += end - begin;
    }

    return retVal / count;
    /*
    using Type = std::int32_t;
    using namespace Alg;
    const auto sourceData = Util::GetRandomVector<Type>(200);

    MergeSort<std::vector<Type>> sorter;
    std::vector<Type> data1(sourceData.size()); // Memory allocation is here

    auto measureSort = [&data1, &sourceData, &sorter]()
    {
        data1 = sourceData;                     // Copying is here

        auto begin = std::chrono::high_resolution_clock::now();
        sorter.Sort(data1);
        auto end = std::chrono::high_resolution_clock::now();

        return (end - begin);
    };

    for (int i = 0; i < 100; i++)
    {
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(measureSort()).count() << std::endl;
    }
    */

    //std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
}

void TestSortingAlgorythms()
{
    using namespace Alg;
    using Type = std::int32_t;
    using TContainer = std::vector < Type > ;
    using TSorter = std::unique_ptr < ISort<TContainer> > ;

    std::vector<std::unique_ptr<ISort<TContainer>>> algs;
    algs.push_back(TSorter(new BubbleSort<TContainer>()));
    algs.push_back(TSorter(new InsertionSort<TContainer>()));
    algs.push_back(TSorter(new MergeSort<TContainer>()));

    for (auto test = 0; test < 100; test++)
    {
        for (auto& sorter : algs)
        {
            auto sourceData = Util::GetRandomVector<Type>(200);
            sorter->Sort(sourceData);

            if (!Util::IsSorted(sourceData))
            {
                // Printing an error message
                Util::CheckTrue(Util::IsSorted(sourceData), __FILE__, __LINE__);
                std::cout << "Failed on following sequence: " << Util::ToString(sourceData) << std::endl;
            }
        }
    }
}

void TestBrackets()
{
    Brackets br;
    Util::CheckTrue(br.CheckBrackets("((){})"), __FILE__, __LINE__);
    Util::CheckTrue(br.CheckBrackets("((){}((({[]}[]))[]{}()))"), __FILE__, __LINE__);
    Util::CheckTrue(br.CheckBrackets("(({}))"), __FILE__, __LINE__);
    Util::CheckFalse(br.CheckBrackets("(({})"), __FILE__, __LINE__);
    Util::CheckFalse(br.CheckBrackets("((){})]"), __FILE__, __LINE__);
    Util::CheckFalse(br.CheckBrackets("()]"), __FILE__, __LINE__);
}

void TestStreams()
{
    Smth s;
    s.ReadFromFile();
}

int main(int argc, char** argv)
{
    /*
    TestMergeSort();

    TestHeap();
    TestBrackets();
    TestSortingAlgorythms();
    */

    TestStreams();
    //MeasureSmth();

    using Type = std::int32_t;
    using TContainer = std::vector < Type > ;
    const std::size_t elementsCount = 10000;
    const std::size_t repetitionCount = 10;
    auto sourceData = Util::GetRandomVector<Type>(elementsCount);

    {
        auto algMerge = [](TContainer& inputData) -> void
        {
            Alg::MergeSort<TContainer> sorter;
            sorter.Sort(inputData);
        };
        auto averageDuration = MeasureSmth(algMerge, sourceData, repetitionCount);
        std::cout << "Avg Merge vector:  " << std::chrono::duration_cast<std::chrono::milliseconds>(averageDuration).count() << std::endl;
    }

    {
        using TContainerList = std::list < Type >;
        auto algMerge = [](TContainerList& inputData) -> void
        {
            Alg::MergeSort<TContainerList> sorter;
            sorter.Sort(inputData);
        };
        TContainerList sourceDataList{ sourceData.begin(), sourceData.end() };
        auto averageDuration = MeasureSmth(algMerge, sourceDataList, repetitionCount);
        std::cout << "Avg Merge list:  " << std::chrono::duration_cast<std::chrono::milliseconds>(averageDuration).count() << std::endl;
    }

    {
        auto algBubble = [](TContainer& inputData) -> void
        {
            Alg::BubbleSort<TContainer> sorter;
            sorter.Sort(inputData);
        };
        auto averageDuration = MeasureSmth(algBubble, sourceData, repetitionCount);
        std::cout << "Avg Bubble: " << std::chrono::duration_cast<std::chrono::milliseconds>(averageDuration).count() << std::endl;
    }

    {
        auto algInsertion = [](TContainer& inputData) -> void
        {
            Alg::InsertionSort<TContainer> sorter;
            sorter.Sort(inputData);
        };
        auto averageDuration = MeasureSmth(algInsertion, sourceData, repetitionCount);
        std::cout << "Avg Insertion: " << std::chrono::duration_cast<std::chrono::milliseconds>(averageDuration).count() << std::endl;
    }

    return 0;
}