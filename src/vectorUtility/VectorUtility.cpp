// VectorUtility.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>

using namespace std;

// ����������� ����������� vector<char> 
// � �������������� ���������.
void show(const char *msg, vector<char> vect)
{
    vector<char>::iterator itr;
    cout << msg;
    for(itr=vect.begin(); itr != vect.end(); ++itr)
    cout << *itr << " ";
    cout << "\n";
}

int main(int argc, char* argv[])
{
	return 0;
}

