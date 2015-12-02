// Inspired by http://habrahabr.ru/post/112222/
#include <iostream>
#include <memory>
#include <cinttypes>
#include <vector>
#include <string>
#include <sstream>

template <typename T>
std::string Print(std::vector<T> data)
{
    std::stringstream s;
    for (auto& item : data) s << item << std::string(", ");
    return s.str();
}

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
        for (std::int64_t i = input.size() / 2; i >= 0; i--)
        {
            Heapify(i);
        }
    }

    void Heapify(std::size_t index)
    {
        T leftChild = 0;
        T rightChild = 0;
        T largestChild = 0;

        for (; ; )
        {
            /*
            левый потомок вершины с индексом i имеет индекс 2*i+1, а правый 2*i+2.
            Корень дерева – элемент с индексом 0.
            */
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
            largestChild = index;

            // Checking if a child exists  && if a child is bigger then parent
            //    vvvvvvvvvvvvvvvvvvv              vvvvvvvvvvvvvvvvvvvvvvv
            if ((leftChild < _data.size()) && (_data[leftChild] > _data[largestChild]))
            {
                largestChild = leftChild;
            }

            // Checking if a child exists  && if a child is bigger then parent
            //    vvvvvvvvvvvvvvvvvvv              vvvvvvvvvvvvvvvvvvvvvvv
            if (rightChild < _data.size() && _data[rightChild] > _data[largestChild])
            {
                largestChild = rightChild;
            }

            // We are done if childs are not exist or they are less then parent
            if (largestChild == index)
            {
                break;
            }

            // Swapping parent and greater child
            T temp = _data[index];
            _data[index] = _data[largestChild];
            _data[largestChild] = temp;
            index = largestChild;
        }
    }

    std::size_t GetSize()
    {
        return _data.size();
    }

    void Push(T value)
    {
        _data.push_back(value);

        int i = _data.size() - 1;
        int parent = (i - 1) / 2;

        while (i > 0 && _data[parent] < _data[i])
        {
            int temp = _data[i];
            _data[i] = _data[parent];
            _data[parent] = temp;

            i = parent;
            parent = (i - 1) / 2;
        }
    }

    const std::vector<T>& GetRaw() const
    {
        return _data;
    }

private:
    std::vector<T> _data;
};

int main(int argc, char** argv)
{
    using Type = std::int32_t;
    std::cout << "Hello, Heap!" << std::endl;

    std::vector<Type> sourceData{ 1, 3, 5, 7, 10, 0, 45, 9, 11 };
    std::cout << "Source array:   " << Print<Type>(sourceData) << std::endl;

    Heap<Type> myHeap(sourceData);
    std::cout << "Heap internals: " << Print<Type>(myHeap.GetRaw()) << std::endl;

    myHeap.Push(100);
    std::cout << "After Push 100: " << Print<Type>(myHeap.GetRaw()) << std::endl;

    myHeap.Push(99);
    std::cout << "After Push 99:  " << Print<Type>(myHeap.GetRaw()) << std::endl;

    return 0;
}