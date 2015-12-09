// http://www.cprogramming.com/tutorial/computersciencetheory/sortcomp.html

// TODO: BubbleSort
// TODO: MergeSort
// TODO: ShellSort
// TODO: QuickSort
// TODO: InsertionSort
#include <utility>
#include <iterator>

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
            RecursiveSort(data, data.begin(), (--data.end()));
        }

    private:
        void RecursiveSort(TContainer& data, const typename TContainer::iterator begin, const typename TContainer::iterator end)
        {
            // If we finally try to sort sequence of 1 element
            // returning because it is already sorted
            if (end == begin)
            {
                return;
            }

            // no needs to split anymore - we already have 2 elements
            // in sequence sort them and return
            if (std::distance(begin, end) == 1)
            {
                if (*begin > *end)
                {
                    std::swap(*begin, *end);
                }
                return;
            }

            // Sequence is bigger then 2 elements. Split it and
            // sort left part and right part independently
            {
                // Getting iterator to the middle of range
                typename TContainer::iterator middleIt = begin;
                std::size_t countToMiddle = (std::distance(begin, end)) / 2;
                std::advance(middleIt, countToMiddle);

                RecursiveSort(data, begin, middleIt);          // Sorting left part
                RecursiveSort(data, std::next(middleIt), end); // Sorting right part

                // Finally merge results
                Merge(data, begin, middleIt, end);
            }
        }

        void Merge(TContainer& data, const typename TContainer::iterator begin, const typename TContainer::iterator middle, const typename TContainer::iterator end)
        {
            /*
            * Merging 2 already sorted sequences (left and right) into one:
            * On each step we take smallest element from each sequence
            * compare them and the one which is less write to result sequence
            * Counter of sequence (left or right) from which we took an element
            * is increased
            */
            typename TContainer::iterator leftIt = begin;
            typename TContainer::iterator rightIt = std::next(middle);
            TContainer resultArray(std::distance(begin, end) + 1);
            for (typename TContainer::iterator i = resultArray.begin(); i != resultArray.end(); i++)
            {
                // If we took all elements from left sequence,
                // simply copy all elements from right sequence
                // to result sequence and finalize
                if (leftIt == data.end() || std::next(middle) == leftIt)
                {
                    for (typename TContainer::iterator j = i; j != resultArray.end(); j++)
                    {
                        *j = *rightIt;
                        rightIt++;
                    }
                    break;
                }
                // If we took all elements from right sequence,
                // simply copy all elements from left sequence
                // to result sequence and finalize
                else if (rightIt == data.end() || std::next(end) == rightIt)
                {
                    for (typename TContainer::iterator j = i; j != resultArray.end(); j++)
                    {
                        *j = *leftIt;
                        leftIt++;
                    }
                    break;
                }

                // Comparing current elements from left and right sequences
                // The smallest one putting to result sequence
                // moving proper current element to the next one
                if (*leftIt < *rightIt)
                {
                    *i = *leftIt;
                    leftIt++;
                }
                else
                {
                    *i = *rightIt;
                    rightIt++;
                }
            }

            // Merged elements are in result sequences
            // copying them to original sequence
            typename TContainer::iterator originalIt = begin;
            for (typename TContainer::iterator i = resultArray.begin(); i != resultArray.end(); i++, originalIt++)
            {
                *originalIt = *i;
            }
        }
    };
}