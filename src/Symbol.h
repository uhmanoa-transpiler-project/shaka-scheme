#ifndef SYMBOL_H
#define SYMBOL_H
#include <boost/flyweight.hpp>
#include <string>

namespace shaka{


class Symbol {
public:
	using Value = std::string;

	//TODO implement interface
	Symbol(Value v) : value(v){}

	Value get_Value() {return value;}	
	// overload the == and != operator for Symbol
	friend bool operator==(const Symbol& n1, const Symbol& n2);
	// hint: == is already overloaded for std::string
	// != can be defined in terms of ==
	friend bool operator!=(const Symbol& n1, const Symbol& n2);
	friend bool operator<(const Symbol& n1, const Symbol& n2);

private:
	std::string value;
};

bool operator<(const Symbol& n1, const Symbol& n2){
	return n1.value[0] < n2.value[0];
}


bool operator==(const Symbol& n1, const Symbol& n2){
	return n1.value == n2.value;
}

bool operator!=(const Symbol& n1, const Symbol& n2){
	return !(n1 == n2);
}

}
#endif
