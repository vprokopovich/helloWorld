#include <iostream>
#include "ExampleOptional.h"
#include "ExampleProgramOptions.h"
#include "ExampleAny.h"

int main(int argc, char** argv)
{
    std::cout << "Hello, World!" << std::endl;

	ExampleOptional example1;
	example1.run();

	ExampleProgramOptions example2(argc, argv);
	example2.run();

	ExampleAny example3;
	example3.run();

    return 0;
}