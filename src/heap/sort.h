// http://www.cprogramming.com/tutorial/computersciencetheory/sortcomp.html

// TODO: BubbleSort
// TODO: MergeSort
// TODO: ShellSort
// TODO: QuickSort
// TODO: InsertionSort
#include <utility>

namespace Alg
{
    template <typename TContainer>
    class ISort
    {
    public:
        virtual void Sort(TContainer& data) = 0;
        virtual ~ISort(){}
    };

    // Complexity O(n^2)
    template <typename TContainer>
    class BubbleSort : public ISort<TContainer>
    {
    public:
        virtual void Sort(TContainer& data) override
        {
            const auto countElements = data.size();

            for (std::size_t i = 0; i < countElements - 1; i++) // (countElements - 1) because we compare current with the next
            {
                bool wasExchange = false;
                for (std::size_t j = 0; j < countElements - i - 1; j++)
                {
                    if (data[j] > data[j + 1])
                    {
                        std::swap(data[j], data[j + 1]);
                        wasExchange = true;
                    }
                }
                if (!wasExchange)
                {
                    break;
                }
            }
        }
    };

    // Complexity O(n^2)
    template <typename TContainer>
    class InsertionSort : public ISort<TContainer>
    {
    public:
        virtual void Sort(TContainer& data) override
        {
            const auto countElements = data.size();
            std::size_t sortedLength = 1; // Assuming first element is already sorted

            // starting from first unsorted, till the last element
            for (std::size_t i = sortedLength; i < countElements; i++)
            {
                std::size_t whereToInsertIndex = sortedLength;
                for (std::size_t j = 0; j<sortedLength; j++)
                {
                    if (data[i] < data[j])
                    {
                        whereToInsertIndex = j;
                        break;
                    }
                }

                Insert(i, whereToInsertIndex, data);
                sortedLength++;
            }
        }

    private:
        void Insert(std::size_t posFrom, std::size_t posTo, TContainer& data)
        {
            auto value = data[posFrom];
            for (std::size_t i = posFrom; i>posTo; i--)
            {
                data[i] = data[i-1];
            }
            data[posTo] = value;
        }
    };

    template <typename TContainer>
    class MergeSort : public ISort<TContainer>
    {
    public:
        virtual void Sort(TContainer& data) override
        {
            RecursiveSort(data, 0, data.size() - 1);
        }

    private:
        void RecursiveSort(TContainer& data, const std::size_t begin, const std::size_t end)
        {
            // If we finally try to sort sequence of 1 element
            // returning because it is already sorted
            if (end == begin)
            {
                return;
            }

            // no needs to split anymore - we already have 2 elements
            // in sequence sort them and return
            if ((end - begin) == 1)
            {
                if (data[begin] > data[end])
                {
                    std::swap(data[begin], data[end]);
                }
                return;
            }

            // Sequence is bigger then 2 elements. Split it and
            // sort left part and right part independently
            {
                auto middleIdx = (end - begin) / 2 + begin;
                RecursiveSort(data, begin, middleIdx);   // Sorting left part
                RecursiveSort(data, middleIdx + 1, end); // Sorting right part

                // Finally merge results
                Merge(data, begin, middleIdx, end);
            }
        }

        void Merge(TContainer& data, const std::size_t begin, const std::size_t middle, const std::size_t end)
        {
            /*
            3.2. Слияние двух подмассивов в третий результирующий массив.
            На каждом шаге мы берём меньший из двух первых элементов подмассивов
            и записываем его в результирующий массив. Счётчики номеров элементов
            результирующего массива и подмассива, из которого был взят элемент, увеличиваем на 1.
            */
            /*
            * Merging 2 already sorted sequences (left and right) into one:
            * On each step we take smallest element from each sequence
            * compare them and the one which is less write to result sequence
            * Counter of sequence (left or right) from which we took an element
            * is increased
            */
            std::size_t arr1Counter = begin;
            std::size_t arr2Counter = middle + 1;
            TContainer resultArray(end - begin + 1);
            for (std::size_t i = 0; i < resultArray.size(); i++)
            {
                // If we took all elements from left sequence,
                // simply copy all elements from right sequence
                // to result sequence and finalize
                if (arr1Counter == middle + 1)
                {
                    for (std::size_t j = i; j < resultArray.size(); j++)
                    {
                        resultArray[j] = data[arr2Counter];
                        arr2Counter++;
                    }
                    break;
                }
                // If we took all elements from right sequence,
                // simply copy all elements from left sequence
                // to result sequence and finalize
                else if (arr2Counter == end + 1)
                {
                    for (std::size_t j = i; j < resultArray.size(); j++)
                    {
                        resultArray[j] = data[arr1Counter];
                        arr1Counter++;
                    }
                    break;
                }

                // Comparing current elements from left and right sequences
                // The smallest one putting to result sequence
                // moving proper current element to the next one
                if ((data[arr1Counter] < data[arr2Counter]))
                {
                    resultArray[i] = data[arr1Counter];
                    arr1Counter++;
                }
                else
                {
                    resultArray[i] = data[arr2Counter];
                    arr2Counter++;
                }
            }

            // Merged elements are in result sequences
            // copying them to original sequence
            for (std::size_t i = 0; i < resultArray.size(); i++)
            {
                data[begin + i] = resultArray[i];
            }
        }
    };
}