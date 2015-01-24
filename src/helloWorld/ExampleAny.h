#ifndef EXAMPLEANY_H
#define EXAMPLEANY_H

#include "ExampleBase.h"
#include <boost/any.hpp>

using namespace boost;
using namespace std;

class ExampleAny : public ExampleBase
{
public:
	void run()
	{
		any w;
		any x {1.0};
		any z = string("test");

		if (false == x.empty())
		{
			cout << "Type: " << x.type().name() << " Value: " << any_cast<double>(x) << endl;

		}

		x = "string";

		if (false == x.empty())
		{
			cout << "Type: " << x.type().name();// << " Value: " << x << endl;
		}
	}
};

#endif // EXAMPLEANY_H