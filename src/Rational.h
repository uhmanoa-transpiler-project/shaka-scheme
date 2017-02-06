#ifndef RATIONAL_H
#define RATIONAL_H

#include "Real.h"

class Rational {
public:
	// constructor
	Rational(int n, int d) : numer(n), denom(d) {}
	
	// implicit type conversion operator for Rational -> Real
	// a rational number is just a real number written as a / b
	// where a and b are whole integers
	// Therefore, to convert to real, we just evaluate the numerator
	// divided by the denominator, casting our numer and denom to
	// doubles prior to executing the division
	operator Real() {
		Real result((double)numer / (double) denom);
		return result;
	}

	// implicit type conversion operator for Rational -> Complex
	// a rational number is just a complex number with an
	// imaginary part that is equal to zero
	operator Complex() {
		Complex result((double)numer / (double) denom, 0);
		return result;
	}


	// getters for supporting unit testing
	int get_numerator();
	int get_denominator();
	
	// arithmetic operators
	 friend Rational operator+(const Rational& lhs, const Rational& rhs);
	 friend Rational operator-(const Rational& lhs, const Rational& rhs);
	 friend Rational operator*(const Rational& lhs, const Rational& rhs);
	 friend Rational operator/(const Rational& lhs, const Rational& rhs);
	

private:
	int numer, denom;
};

int Rational::get_numerator() {
	return numer;
}

int Rational::get_denominator() {
	return denom;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
	double new_numer = lhs.numer * rhs.denom + rhs.numer * lhs.denom;
	double new_denom = lhs.denom * rhs.denom;
	Rational result(new_numer, new_denom);
	return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
	double new_numer = lhs.numer * rhs.denom - rhs.numer * lhs.denom;
	double new_denom = lhs.denom * rhs.denom;
	Rational result(new_numer, new_denom);
	return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
	Rational result(lhs.numer * rhs.numer, lhs.denom * rhs.denom);
	return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	Rational result(lhs.numer * rhs.denom, lhs.denom * rhs.numer);
	return result;
}
#endif
