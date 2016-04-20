#include <iostream>     // for std::cout
#include <cinttypes>    // for type definitions
#include <vector>
#include <list>
#include <memory>
#include <functional>

#include "helpers.h"
#include "heap.h"
#include "sort.h"
#include "brackets.h"
#include "streamTest.h"
#include "measurements.h"
#include "smallExperiments.h"

void RunSmallExperiments()
{
    UnexpectedSizeOfClass            example1; example1.Run();
    DoNotThrowExceptionInConstructor example2; example2.Run();
}

void TestHeap()
{
    using Type = std::int32_t;
    using namespace Alg;

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

void MeasureSorts()
{
    const std::size_t elementsCount = 10000;
    const std::size_t repetitionCount = 10;

    using namespace std::chrono;
    using Type = std::int32_t;
    using TContainer = std::vector < Type > ;

    auto sourceData = Util::GetRandomVector<Type>(elementsCount);

    {
        auto algStd = [](TContainer& inputData) -> void
        {
            std::sort(inputData.begin(), inputData.end());
        };
        auto averageDuration = Util::Measure(algStd, sourceData, repetitionCount);
        std::cout << "Avg std::sort: " << duration_cast<milliseconds>(averageDuration).count() << "ms" << std::endl;
    }

    {
        auto algMerge = [](TContainer& inputData) -> void
        {
            Alg::MergeSort<TContainer> sorter;
            sorter.Sort(inputData);
        };
        auto averageDuration = Util::Measure(algMerge, sourceData, repetitionCount);
        std::cout << "Avg Merge vector:  " << duration_cast<milliseconds>(averageDuration).count() << "ms" << std::endl;
    }

    {
        using TContainerList = std::list < Type >;
        auto algMerge = [](TContainerList& inputData) -> void
        {
            Alg::MergeSort<TContainerList> sorter;
            sorter.Sort(inputData);
        };
        TContainerList sourceDataList{ sourceData.begin(), sourceData.end() };
        auto averageDuration = Util::Measure(algMerge, sourceDataList, repetitionCount);
        std::cout << "Avg Merge list:  " << duration_cast<milliseconds>(averageDuration).count() << "ms" << std::endl;
    }

    {
        auto algBubble = [](TContainer& inputData) -> void
        {
            Alg::BubbleSort<TContainer> sorter;
            sorter.Sort(inputData);
        };
        auto averageDuration = Util::Measure(algBubble, sourceData, repetitionCount);
        std::cout << "Avg Bubble: " << duration_cast<milliseconds>(averageDuration).count() << "ms" << std::endl;
    }

    {
        auto algInsertion = [](TContainer& inputData) -> void
        {
            Alg::InsertionSort<TContainer> sorter;
            sorter.Sort(inputData);
        };
        auto averageDuration = Util::Measure(algInsertion, sourceData, repetitionCount);
        std::cout << "Avg Insertion: " << duration_cast<milliseconds>(averageDuration).count() << "ms" << std::endl;
    }
}

int main(int argc, char** argv)
{
    try
    {
        RunSmallExperiments();
        TestHeap();
        TestBrackets();
        TestSortingAlgorythms();
        TestStreams();
        MeasureSorts();
    }
    catch (...)
    {
        std::cout << "!!!!! If you see this message then something went wrong in one of tests" << std::endl;
        return 201; // Some value that differs from 0
    }

    return 0; // Program is terminated as expected
}