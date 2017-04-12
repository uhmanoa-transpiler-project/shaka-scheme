#ifndef BOOLEAN_H
#define BOOLEAN_H

namespace shaka{


class Boolean {
public:


	//TODO implement interface
	Boolean(bool v) : value(v){}

	bool get_value() {return value;}	
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

}
#endif
