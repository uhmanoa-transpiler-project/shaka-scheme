#ifndef SYMBOL_H
#define SYMBOL_H
#include <boost/flyweight.hpp>
#include <string>




class Symbol {
public:
	//TODO implement interface
	// overload the == and != operator for Symbol
	// hint: == is already overloaded for std::string
	// != can be defined in terms of ==
private:
	std::string value;
};

#endif
