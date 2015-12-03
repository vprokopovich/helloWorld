#include <iostream>     // for std::cout
#include <cinttypes>    // for type definitions
#include <vector>
#include <algorithm>    // for std::make_heap

#include "helpers.h"
#include "heap.h"

int main(int argc, char** argv)
{
    using Type = std::int32_t;

    const std::vector<Type> sourceData{ 1, 3, 5, 7, 10, 0, 45, 9, 11 };
    std::cout << "Source array:   " << Print<Type>(sourceData) << std::endl;

    // Creating own heap
    Heap<Type> myHeap(sourceData);

    // Creating std::heap
    auto stdHeap = sourceData;
    std::make_heap(stdHeap.begin(), stdHeap.end());

    std::cout << "Heap internals: " << Print<Type>(myHeap.GetRaw()) << std::endl;

    // Pushing to own heap
    myHeap.Push(100);
    myHeap.Push(99);

    // Pushing to std::heap
    stdHeap.push_back(100);
    std::push_heap(stdHeap.begin(), stdHeap.end());
    stdHeap.push_back(99);
    std::push_heap(stdHeap.begin(), stdHeap.end());

    std::cout << "Heap internals after pushing values: " << Print(myHeap.GetRaw()) << std::endl;

    std::cout << (Compare(myHeap.GetRaw(), stdHeap) ? "OK" : "Fail") << std::endl;

    return 0;
}