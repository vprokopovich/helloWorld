
#include <string>
#include <stdlib.h>
#include <time.h>
#include <limits>



#include "ProgramGeneticHW.h"

namespace
{
    const std::size_t MUTATIONS_COUNT = 4;

    /*
    * Calculates distance between 2 operands
    */
    template <typename T>
    int Distance(T op1, T op2)
    {
        return std::abs(op1 - op2);
    }

    char GetRandomChar()
    {
        return (rand() % 256) + std::numeric_limits<char>::min();
    }
    Thing::TIndex GetRandomIndex(Thing::TIndex max)
    {
        return (rand() % max);
    }
}

Thing::Thing(const std::string& initialString)
    : _properties(initialString.begin(), initialString.end()) // copying initialString to _properties
{
}

std::set<Thing::TIndex> Thing::ChangeRandomly(std::size_t howMuch = MUTATIONS_COUNT)
{
    const TIndex propertiesCount = _properties.size();
    for (TIndex i = 0; i < MUTATIONS_COUNT; i++)
    {
        _properties.at(GetRandomIndex(propertiesCount)) = GetRandomChar();
    }
}

void ProgramGeneticHW::Run()
{
    srand(time(NULL)); // random generator init

    Thing t("Hello world");

    for (int i = 0; i<10; i++)
    {
        t.ChangeRandomly(2);
        std::cout << t << std::endl;
        //std::cout << static_cast<int>(GetRandom<char>()) << "  ";
    }
}