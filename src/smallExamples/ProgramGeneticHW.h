#include <vector>
#include <set>
#include <iostream>
#include <iterator>

class Thing
{
public:
    using TIndex = std::size_t;

    Thing(const std::string& initialString);

    /*
    * Returns set of indexes which were changed
    */
    std::set<TIndex> ChangeRandomly(std::size_t howMuch = MUTATIONS_COUNT);

    friend std::ostream& operator<<(std::ostream& os, const Thing& thing);
private:
    std::vector<char> _properties;
};

//template <typename T>
std::ostream& operator<<(std::ostream& os, const Thing& thing)
{
    if (!thing._properties.empty())
    {
        std::copy(thing._properties.begin(), thing._properties.end(), std::ostream_iterator<char>(os/*, ", "*/));
    }

    return os;
}

class ProgramGeneticHW
{
public:
    void Run();
};