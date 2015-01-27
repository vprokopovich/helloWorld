#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class JsonParsingException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Json document parsing error";
	}
};

#endif // EXCEPTIONS_H