#ifndef SHAKA_CORE_BASE_BOOLEAN_H
#define SHAKA_CORE_BASE_BOOLEAN_H
#include <iostream>
namespace shaka{


class Boolean {
public:
	//TODO implement interface
	Boolean(bool v) : value(v){}

	bool get_value() const {return value;}	
    void set_value(bool v) { value = v; }

    
	// overload the == and != operator for Boolean
	friend bool operator==(const Boolean& n1, const Boolean& n2);
	// hint: == is already overloaded for std::string
	// != can be defined in terms of ==
	friend bool operator!=(const Boolean& n1, const Boolean& n2);

private:
	bool value;
};

bool operator==(const Boolean& n1, const Boolean& n2){
	return n1.value == n2.value;
}

bool operator!=(const Boolean& n1, const Boolean& n2){
	return !(n1 == n2);
}


std::ostream& operator<< (std::ostream& lhs, const shaka::Boolean& rhs) {
    lhs << ((rhs.get_value()) ? "#t" : "#f");
    return lhs;
}
}
#endif // SHAKA_CORE_BASE_BOOLEAN_H
