#pragma once
// Inspired by http://habrahabr.ru/post/112222/

#include <vector>
#include <utility>      // for std::swap
#include <algorithm>    // for std::make_heap

namespace Alg
{
    template <typename T>
    class IHeap
    {
    public:
        /*
        * Returns size of heap
        * @return size
        */
        virtual std::size_t GetSize() = 0;

        /*
        * Pushes a value to a heap. Size increases
        * @param value The value to be stored
        */
        virtual void Push(T value) = 0;

        /*
        * Pops a max value from the heap. Size decreases.
        * @throw std::out_of_range in case if heap is empty
        * @return Max value stored in the heap
        */
        virtual T Pop() = 0;

        /*
        * Provides reference to internal buffer. Is used for testing purposes
        * @return vector
        */
        virtual const std::vector<T>& GetRaw() const = 0;

        /*
        * Virtual destructor
        */
        virtual ~IHeap() {};
    };

    template <typename T>
    class MyHeap : public IHeap < T >
    {
    public:

        /*
        * Takes some vector with values and transforms it into heap
        */
        MyHeap(const std::vector<T> input)
            : _data(input)
        {
            Init();
        }

        MyHeap(std::initializer_list<T> values)
            : _data(values)
        {
            Init();
        }

        ~MyHeap(){}

        virtual std::size_t GetSize() override
        {
            return _data.size();
        }

        virtual void Push(T value) override
        {
            _data.push_back(value);

            int newElementIndex = _data.size() - 1;     // As element was pushed back to vector, it is expected that new element is the last in vector
            int parent = (newElementIndex - 1) / 2;

            while (newElementIndex > 0 && _data[parent] < _data[newElementIndex])
            {
                std::swap(_data[newElementIndex], _data[parent]);
                newElementIndex = parent;
                parent = (newElementIndex - 1) / 2;
            }
        }

        virtual T Pop() override
        {
            if (_data.empty())
            {
                throw std::out_of_range("Heap is empty");
            }

            T retVal = _data[0];
            _data[0] = _data.back();
            _data.pop_back();
            Heapify(0);

            return retVal;
        }

        virtual const std::vector<T>& GetRaw() const override
        {
            return _data;
        }

    private:
        void Init()
        {
            for (std::int64_t i = static_cast<std::int64_t>(_data.size() / 2); i >= 0; i--) // TODO: should be reworked to avoid signed values
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

    private:
        std::vector<T> _data;
    };

    template <typename T>
    class StdHeap : public IHeap < T >
    {
    public:
        /*
        * Takes some vector with values and transforms it into heap
        */
        StdHeap(const std::vector<T> input)
            : _data(input)
        {
            std::make_heap(_data.begin(), _data.end());
        }

        ~StdHeap(){}

        virtual std::size_t GetSize() override
        {
            return _data.size();
        }

        virtual void Push(T value) override
        {
            _data.push_back(value);
            std::push_heap(_data.begin(), _data.end());
        }

        virtual T Pop() override
        {
            if (_data.empty())
            {
                throw std::out_of_range("Heap is empty");
            }
            T retVal = _data[0];
            std::pop_heap(_data.begin(), _data.end());
            _data.pop_back();
            return retVal;
        }

        virtual const std::vector<T>& GetRaw() const override
        {
            return _data;
        }

    private:
        std::vector<T> _data;
    };
}