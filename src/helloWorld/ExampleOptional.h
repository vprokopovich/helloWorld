#ifndef EXAMPLEOPTIONAL_H
#define EXAMPLEOPTIONAL_H

#include "ExampleBase.h"
#include <boost/optional.hpp>

using namespace boost;
using namespace std;

struct Person
{
    Person(string name, string surname)
    : mName(name)
    , mSurname(surname)
    , mMiddlename()
    {

    }

    Person(string name, string surname, string middlename)
    : mName(name)
    , mSurname(surname)
    , mMiddlename(middlename)
    {

    }

    string mName;
    string mSurname;
    optional<string> mMiddlename;
};


class ExampleOptional : public ExampleBase
{
public:
	void run()
	{
		Person person1 = {"Name 1", "Surname 1", "Middlename 1"};
		Person person2 = {"Name 2", "Surname 2"};
		person2.mSurname = "Surname 2";
		Person person3 = {"NAme 3", "Surname 3"};

		cout << person1.mName << " " << person1.mSurname << " " << ((person1.mMiddlename) ? *person1.mMiddlename : "No Middle Name") << endl;
		cout << person2.mName << " " << person2.mSurname << " " << ((person2.mMiddlename) ? *person2.mMiddlename : "No Middle Name") << endl;
		cout << person3.mName << " " << person3.mSurname << " " << ((person3.mMiddlename) ? *person3.mMiddlename : "No Middle Name") << endl;

	}
};

#endif // EXAMPLEOPTIONAL_H