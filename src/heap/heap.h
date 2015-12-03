#pragma once
// Inspired by http://habrahabr.ru/post/112222/

#include <vector>
#include <utility>      // for std::swap

template <typename T>
class Heap
{
public:

    /*
    * Takes some vector with values and transforms it into heap
    */
    explicit Heap(const std::vector<T> input)
        : _data(input)
    {
        for (std::int64_t i = static_cast<std::int64_t>(input.size() / 2); i >= 0; i--) // TODO: should be reworked to avoid signed values
        {
            Heapify(i);
        }
    }

    void Heapify(std::int64_t index)
    {
        T leftChild = 0;
        T rightChild = 0;
        T largestChild = 0;

        for (;;)
        {
            /*
            * left child of the node with index i has index (2 * i + 1)
            * right child of the node with index i has index (2 * i + 2)
            * The root of heap has index 0
            **/
            leftChild = 2 * index + 1;      // TODO: fix warning
            rightChild = 2 * index + 2;     // TODO: fix warning
            largestChild = index;           // TODO: fix warning

            // Checking if a child exists  && if a child is bigger then parent
            //    vvvvvvvvvvvvvvvvvvv              vvvvvvvvvvvvvvvvvvvvvvv
            if ((leftChild < _data.size()) && (_data[leftChild] > _data[largestChild]))
            {
                largestChild = leftChild;
            }

            // Checking if a child exists  && if a child is bigger then parent
            //    vvvvvvvvvvvvvvvvvvv              vvvvvvvvvvvvvvvvvvvvvvv
            if (rightChild < _data.size() && _data[rightChild] > _data[largestChild])     // TODO: fix warning
            {
                largestChild = rightChild;
            }

            // We are done if childs are not exist or they are less then parent
            if (largestChild == index)
            {
                break;
            }

            // Swapping parent and greater child
            //Swap(_data[index], _data[largestChild]);
            std::swap(_data[index], _data[largestChild]);
            index = largestChild;
        }
    }

    inline std::size_t GetSize()
    {
        return _data.size();
    }

    void Push(T value)
    {
        _data.push_back(value);

        int newElementIndex = _data.size() - 1;     // As element was pushed back to vector, it is expected that new element is the last in vector
        int parent = (newElementIndex - 1) / 2;     // Why expecting it is a left element ???

        while (newElementIndex > 0 && _data[parent] < _data[newElementIndex])
        {
            std::swap(_data[newElementIndex], _data[parent]);
            newElementIndex = parent;
            parent = (newElementIndex - 1) / 2;
        }
    }

    const std::vector<T>& GetRaw() const
    {
        return _data;
    }

private:

    std::vector<T> _data;
};