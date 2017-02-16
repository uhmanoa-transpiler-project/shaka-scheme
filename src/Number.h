#ifndef NUMBER_H
#define NUMBER_H
#include <cmath>
#include <boost/variant.hpp>
#include <typeinfo>
#include "Integer.h"

namespace shaka {

using Value = boost::variant<Integer, Real>;
		
Value operator+(Value v1, Value v2) {
	if (v1.type() == typeid(Integer)) {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Integer>(v1) + boost::get<Integer>(v2);
		}
		else {
			return boost::get<Integer>(v1) + boost::get<Real>(v2);
		}
	}
	else {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Real>(v1) + boost::get<Integer>(v2);
		}
		else {
			return boost::get<Real>(v1) + boost::get<Real>(v2);
		}
	}


}


class Number {
public:


	
	// default and initialization constructors
	Number() : value(0) {}	
	Number(shaka::Value v) : value(v) {}
	Number(const Number& other) : value(other.value) {}
	
    shaka::Value get_value() {return value;}
	// arithmetic operators R7RS 6.2.6
	friend Number operator+(const Number& n1, const Number& n2);
	/*
	friend Number operator-(const Number& n1, const Number& n2);
	friend Number operator*(const Number& n1, const Number& n2);
	friend Number operator/(const Number& n1, const Number& n2);
	
	// comparison operators R7RS 6.2.6
	friend bool operator==(const Number& n1, const Number& n2);
	friend bool operator!=(const Number& n1, const Number& n2);
	friend bool operator>(const Number& n1, const Number& n2);
	friend bool operator<(const Number& n1, const Number& n2);
	friend bool operator>=(const Number& n1, const Number& n2);
	friend bool operator<=(const Number& n1, const Number& n2);
	
	// testing for exactness/inexactness R7RS 6.2.2
	friend bool exact_p(const Number& n);
	friend bool inexact_p(const Number& n);

	// numerical predicates testing a number for a particular property R7RS 6.2.6
	friend bool zero_p(const Number& n);
	friend bool positive_p(const Number& n);
	friend bool negative_p(const Number& n);
	friend bool odd_p(const Number& n);
	friend bool even_p(const Number& n);
	
	// max and min of two numbers R7RS 6.2.6
	friend Number max(const Number& n1, const Number& n2);
	friend Number min(const Number& n1, const Number& n2);
	

	friend Number abs(const Number& n);

	friend Number floor(const Number& n);
	friend Number ceiling(const Number& n);
	friend Number truncate(const Number& n);
	friend Number round(const Number& n);

	friend Number gcd(const Number& n1, const Number& n2);
	friend Number lcm(const Number& n1, const Number& n2);

	friend Number square(const Number& n);
	friend Number sqrt(const Number& n);
	*/

private:

	shaka::Value value;	
};


//---------------------------------------------------
// Arithmetic operator overloads
//---------------------------------------------------
Number operator+(const Number& n1, const Number& n2) {
	Number result(n1.value + n2.value);
	return result;
}
/*
Number operator-(const Number& n1, const Number& n2) {
	Number result(n1.value - n2.value);
	return result;
}

Number operator*(const Number& n1, const Number& n2) {
	Number result(n1.value * n2.value);
	return result;
}

Number operator/(const Number& n1, const Number& n2) {
	Number result(n1.value / n2.value);
	return result;
}

//---------------------------------------------------
// Comparison operator overloads
//--------------------------------------------------
bool operator==(const Number& n1, const Number& n2) {
	return n1.value == n2.value;
}

bool operator!=(const Number& n1, const Number& n2) {
	return !(n1 == n2);
}

bool operator>(const Number& n1, const Number& n2) {
	return n1.value > n2.value;
}

bool operator<(const Number& n1, const Number& n2) {
	return n1.value < n2.value;
}

bool operator>=(const Number& n1, const Number& n2) {
	return n1.value >= n2.value;
}

bool operator<=(const Number& n1, const Number& n2) {
	return n1.value <= n2.value;
}

//---------------------------------------------------
// Built-in Numeric Predicates
//---------------------------------------------------
bool exact_p(const Number& n) {
	return n.value == trunc(n.value);
}

bool inexact_p(const Number& n) {
	return !(exact_p(n));
}

bool zero_p(const Number& n) {
	return (n.value == 0);
}

bool positive_p(const Number& n) {
	return (n.value > 0);
}

bool negative_p(const Number& n) {
	return (n.value < 0);
}

bool even_p(const Number& n) {
	return (n.value % 2 == 0);
}

bool odd_p(const Number& n) {
	return !(even_p(n));
}

//------------------------------------------------
// Max and Min of two Numbers: Built-in
//------------------------------------------------

Number max(const Number& n1, const Number& n2) {
	if (n1 >= n2) {
		return n1;
	}
	else {
		return n2;
	}
}

Number min(const Number& n1, const Number& n2) {
	if (n1 <= n2) {
		return n1;
	}
	else {
		return n2;
	}
}
*/
} // namespace shaka

#endif // NUMBER_H
