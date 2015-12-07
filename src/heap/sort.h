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

    template <typename TContainer>
    class BubbleSort : public ISort<TContainer>
    {
    public:
        virtual void Sort(TContainer& data) override
        {
            const auto countElements = data.size();

            for (auto i = 0; i < countElements - 1; i++) // (countElements - 1) because we compare current with the next
            {
                bool wasExchange = false;
                for (auto j = 0; j < countElements - i - 1; j++)
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

    template <typename TContainer>
    class InsertionSort : public ISort<TContainer>
    {
    public:
        virtual void Sort(TContainer& data) override
        {
            const auto countElements = data.size();
            std::size_t sortedLength = 1; // Assuming first eleent is already sorted

            // starting from first unsorted, til the last element
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

                std::cout << "Decided to place it to index:" << whereToInsertIndex << std::endl;

                Insert(i, whereToInsertIndex, data);
                sortedLength++;

                std::cout << "Got: " << Util::ToString(data) << std::endl;
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
}