#ifndef REAL_H
#define REAL_H
#include "Complex.h"
#include <cmath>
class Real {
public:
	Real(double v) : value(v) {}
	
	// implicit type conversion operator for Real -> Complex
	// a real number is just a complex number with an imaginary
	// part that is equal to zero
        operator Complex() {
		Complex result(value, 0);
		return result;
	}
	
	// arithmetic operators
	friend Real operator+(const Real& lhs, const Real& rhs);
	friend Real operator-(const Real& lhs, const Real& rhs);
	friend Real operator*(const Real& lhs, const Real& rhs);
	friend Real operator/(const Real& lhs, const Real& rhs);

	// comparison operators
	friend bool operator==(const Real& lhs, const Real& rhs);
	friend bool operator>(const Real& lhs, const Real& rhs);
	friend bool operator<(const Real& lhs, const Real& rhs);
	friend bool operator>=(const Real& lhs, const Real& rhs);
	friend bool operator<=(const Real& lhs, const Real& rhs);
	friend bool operator!=(const Real& lhs, const Real& rhs);

	double get_value();


private:
	double value;
};

double Real::get_value() {
	return value;
}

Real operator+(const Real& lhs, const Real& rhs) {
	Real result(lhs.value + rhs.value);
	return result;
}

Real operator-(const Real& lhs, const Real& rhs) {
	Real result(lhs.value - rhs.value);
	return result;
}

Real operator*(const Real& lhs, const Real& rhs) {
	Real result(lhs.value * rhs.value);
	return result;
}

Real operator/(const Real& lhs, const Real& rhs) {
	Real result(lhs.value / rhs.value);
	return result;
}

bool operator==(const Real& lhs, const Real& rhs) {
	return lhs.value == rhs.value;
}

bool operator>(const Real& lhs, const Real& rhs) {
	return lhs.value > rhs.value;
}

bool operator<(const Real& lhs, const Real& rhs) {
	return lhs.value < rhs.value;
}

bool operator>=(const Real& lhs, const Real& rhs) {
	return lhs.value >= rhs.value;
}

bool operator<=(const Real& lhs, const Real& rhs) {
	return lhs.value <= rhs.value;
}

bool operator!=(const Real& lhs, const Real& rhs) {
	return lhs.value != rhs.value;
}

#endif
