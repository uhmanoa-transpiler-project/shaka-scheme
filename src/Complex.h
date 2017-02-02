#ifndef COMPLEX_H
#define COMPLEX_H
#include "Number.h"
Class Complex : public Number {
public:
	Complex(double r, double i) : real(r), imag(i) {}
	Complex(Complex& c) : real(c.real), imag(c.imag) {}
	~Complex() {}
	virtual Complex operator+(const Complex& lhs, const Complex& rhs) const override {}
	virtual Complex operator-(const Complex& lhs, const Complex& rhs) const override {}
	virtual Complex operator*(const Complex& lhs, const Complex& rhs) const override {}
	virtual Complex operator/(const Complex& lhs, const Complex& rhs) const override {}
	virtual bool operator==(const Complex& lhs, const Complex& rhs) const override {}
private:
	double real, imag;
	};
#endif









