#ifndef INTEGER_H
#define INTEGER_H
#include "Rational.h"
class Integer {
public:
	~Integer() {}
	Integer(int v) : value(v) {}
	Integer(const Integer& i) : value(i.value) {}


	// implicit conversion operator for Integer -> Rational
	// An Integer is just a Rational with a denominator equal to 1
	// And a numerator equal to its value
	operator Rational() {
		Rational result(value, 1);
		return result;
	}

	// implicit conversion operator for Integer -> Real
	// An Integer is converted to a Real by casting its
	// value to a double
	operator Real() {
		Real result((double)value);
		return result;
	}
	
	// implicit conversion operator for Integer -> Complex
	// Like a Real, an Integer is just a complex number
	// With an imaginary part equal to 0
	operator Complex() {
		Complex result((double)value, 0);
		return result;
	}
	
	// arithmetic operators for Integers
	friend Integer operator+(const Integer& lhs, const Integer& rhs);
	friend Integer operator-(const Integer& lhs, const Integer& rhs);
	friend Integer operator*(const Integer& lhs, const Integer& rhs);
	friend Integer operator/(const Integer& lhs, const Integer& rhs);

	// comparison operators for Integers
	friend bool operator==(const Integer& lhs, const Integer& rhs);
	friend bool operator>(const Integer& lhs, const Integer& rhs);
	friend bool operator<(const Integer& lhs, const Integer& rhs);
	friend bool operator>=(const Integer& lhs, const Integer& rhs);
	friend bool operator<=(const Integer& lhs, const Integer& rhs);
	friend bool operator!=(const Integer& lhs, const Integer& rhs);

	int get_value();
private:
	int value;
};

int Integer::get_value() {
	return value;
}

Integer operator+(const Integer& lhs, const Integer& rhs) {
	Integer result(lhs.value + rhs.value);
	return result;
}

Integer operator-(const Integer& lhs, const Integer& rhs) {
	Integer result(lhs.value - rhs.value);
	return result;
}

Integer operator*(const Integer& lhs, const Integer& rhs) {
	Integer result(lhs.value * rhs.value);
	return result;
}

Integer operator/(const Integer& lhs, const Integer& rhs) {
	Integer result(lhs.value / rhs.value);
	return result;
}

bool operator==(const Integer& lhs, const Integer& rhs) {
	return lhs.value == rhs.value;
}

bool operator>(const Integer& lhs, const Integer& rhs) {
	return lhs.value > rhs.value;
}

bool operator<(const Integer& lhs, const Integer& rhs) {
	return lhs.value < rhs.value;
}

bool operator>=(const Integer& lhs, const Integer& rhs) {
	return lhs.value >= rhs.value;
}

bool operator<=(const Integer& lhs, const Integer& rhs) {
	return lhs.value <= rhs.value;
}

bool operator!=(const Integer& lhs, const Integer& rhs) {
	return lhs.value != rhs.value;
}



#endif
