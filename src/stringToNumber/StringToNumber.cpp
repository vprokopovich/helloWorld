// StringToNumber.cpp : Defines the entry point for the console application.
//
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
T stringToInt (string str)
{
    T retVal = 0;

    const size_t typeLength = sizeof(T) * 8; // calculating max length of possible string to be processed
    if (str.length() > typeLength)  // getting substring if neccessary to get into max length
    {
        str = str.substr((str.length() - typeLength), typeLength);
    }

    // checking string to contain only 0 an 1
    for (int i=0; i < std::min(typeLength, str.length()); i++)
    {
        retVal = retVal << 1;
        if ((str.at(i) != '0') && (str.at(i) != '1'))
        {
            //cout << "incorrect symbol at pos: " << i << endl;
            retVal = 0;
            break;
        }
        retVal += (str.at(i) == '1') ? 1 : 0;
    }
    
    //cout << str << endl;

    return retVal;
}



int main(int argc, char* argv[])
{
	unsigned int a1 = stringToInt<unsigned int>("1010101011110101010101");
    unsigned int a2 = stringToInt<unsigned int>("1000");
    unsigned int a3 = stringToInt<unsigned int>("100011111111111111111");
    unsigned int a4 = stringToInt<unsigned int>("10001111");
    unsigned int a5 = stringToInt<unsigned int>("10001111a");

    return 0;
}

