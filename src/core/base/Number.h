#ifndef NUMBER_H
#define NUMBER_H

#include <cmath>
#include "core/base/Value.h"

namespace shaka {

class Number {
public:
	
	// default and initialization constructors
	Number() : value(Integer(0)) {}	
	Number(Value v) : value(v) {}
	Number(const Number& other) : value(other.value) {}

	// conversion constructors
	Number(int v) : value(Integer(v)) {}
	Number(double v) : value(Real(v)) {}
	Number(int n, int d) : value(Rational(n, d)) {}
	
    Value get_value() {return value;}

	// arithmetic operators R7RS 6.2.6
	friend Number operator+(const Number& n1, const Number& n2);
	friend Number operator-(const Number& n1, const Number& n2);
	friend Number operator*(const Number& n1, const Number& n2);
	friend Number operator/(const Number& n1, const Number& n2);
	friend Number operator|(const Number& n1, const Number& n2);
	friend Number operator%(const Number& n1, const Number& n2);	

	// comparison operators R7RS 6.2.6
	friend bool operator==(const Number& n1, const Number& n2);
	friend bool operator!=(const Number& n1, const Number& n2);
	friend bool operator>(const Number& n1, const Number& n2);
	friend bool operator<(const Number& n1, const Number& n2);
	friend bool operator>=(const Number& n1, const Number& n2);
	friend bool operator<=(const Number& n1, const Number& n2);
	
    friend std::ostream& operator<< (std::ostream& lhs, const Number& rhs);

	// testing for exactness/inexactness R7RS 6.2.2
	bool exact_p();
	bool inexact_p();
	/*
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

	Value value;	
};


//---------------------------------------------------
// Arithmetic operator overloads
//---------------------------------------------------
Number operator+(const Number& n1, const Number& n2) {
	Number result(n1.value + n2.value);
	return result;
}

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

Number operator|(const Number& n1, const Number& n2) {
	Number result(n1.value | n2.value);
	return result;
}

Number operator%(const Number& n1, const Number& n2) {
	Number result(n1.value % n2.value);
	return result;
}
//---------------------------------------------------
// Comparison operator overloads
//--------------------------------------------------
bool operator==(const Number& n1, const Number& n2) {
	return value_eq_p(n1.value, n2.value);
}

bool operator!=(const Number& n1, const Number& n2) {
	return !(n1 == n2);
}

bool operator<(const Number& n1, const Number& n2) {
	return value_lt_p(n1.value, n2.value);
}

bool operator>(const Number& n1, const Number& n2) {
	return !(n1 == n2) && !(n1 < n2);
}

bool operator>=(const Number& n1, const Number& n2) {
	return (n1 > n2) || (n1 == n2);
}

bool operator<=(const Number& n1, const Number& n2) {
	return (n1 < n2) || (n1 == n2);
}

//---------------------------------------------------
// Built-in Numeric Predicates
//---------------------------------------------------
bool Number::exact_p() {
	return !(this->value.type() == typeid(shaka::Real));
}

bool Number::inexact_p() {
	return !this->exact_p();
}
/*
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

std::ostream& operator<< (std::ostream& lhs, const Number& rhs) {
    if (auto* p = boost::get<shaka::Integer>(&rhs.value)) {
        lhs << p->get_value();
    }
    else if (auto* p = boost::get<shaka::Rational>(&rhs.value)) {
        lhs << p->get_numerator() << '/' << p->get_denominator();
    }
    else if (auto* p = boost::get<shaka::Real>(&rhs.value)) {
        lhs << p->get_value();
    }
    else {
        throw std::runtime_error("Number.<<: Invalid variant type");
    }
    return lhs;
}

} // namespace shaka

#endif // NUMBER_H
