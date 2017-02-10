#ifndef NUMBER_H
#define NUMBER_H
#include <cmath>

namespace shaka {

class Number {
public:

	using Value = double;

	Number() : value(0) {}	
	Number(Value v) : value(v) {}
	

	Value get_Value() {return value;}
	// arithmetic operators
	friend Number operator+(const Number& n1, const Number& n2);
	friend Number operator-(const Number& n1, const Number& n2);
	friend Number operator*(const Number& n1, const Number& n2);
	friend Number operator/(const Number& n1, const Number& n2);

	// comparison operators
	friend bool operator==(const Number& n1, const Number& n2);
	friend bool operator!=(const Number& n1, const Number& n2);
	friend bool operator>(const Number& n1, const Number& n2);
	friend bool operator<(const Number& n1, const Number& n2);
	friend bool operator>=(const Number& n1, const Number& n2);
	friend bool operator<=(const Number& n1, const Number& n2);


	friend bool exact_p(const Number& n);
	friend bool inexact_p(const Number& n);
	/* 
	friend bool zero_p(const Number& n);
	friend bool positive_p(const Number& n);
	friend bool negative_p(const Number& n);
	friend bool odd_p(const Number& n);
	friend bool even_p(const Number& n);

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

bool exact_p(const Number& n) {
	return n.value == trunc(n.value);
}

bool inexact_p(const Number& n) {
	return !(exact_p(n));
}
} // namespace shaka

#endif // NUMBER_H
