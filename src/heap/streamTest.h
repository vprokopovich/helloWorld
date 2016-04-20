#include <fstream>
#include <vector>
#include <cinttypes>
#include <string>

class Smth
{
public:
    std::vector<std::string> ReadFromFile()
    {
        std::string input, output;
        //std::cout << "<input filename> <output filename>:" << std::endl;

        input = "input.txt";
        output = "output.txt";

        //std::cout << "input=" << input << "   output=" << output << std::endl;

        std::ifstream inputFileStream{ input };

        return std::vector<std::string>();
    }
};