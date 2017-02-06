#ifndef COMPLEX_H
#define COMPLEX_H
#include <cmath>
class Complex {
public:
	Complex() {};	
	Complex(double r, double i) : real(r), imag(i) {};

	// we declare these arithmetic operators as friends of the class
	// to support the ability to invoke binary operators on differing
	// numeric types i.e. Integer + Complex, Rational + Complex, etc.
	// for which we have defined an implicit type conversion
	friend Complex operator+(const Complex& lhs, const Complex& rhs);
	friend Complex operator-(const Complex& lhs, const Complex& rhs);
	friend Complex operator*(const Complex& lhs, const Complex& rhs);
	friend Complex operator/(const Complex& lhs, const Complex& rhs);
	
	// getter methods, for unit testing support
	double get_real();
	double get_imag();
private:
	double real, imag;
};

double Complex::get_real() {
	return real;
}

double Complex::get_imag() {
	return imag;
}

Complex operator+(const Complex& lhs, const Complex& rhs) {
	Complex result(lhs.real + rhs.real, lhs.imag + rhs.imag);
	return result;
}

Complex operator-(const Complex& lhs, const Complex& rhs) {
        Complex result(lhs.real - rhs.real, lhs.imag - rhs.imag);
        return result;
}

Complex operator*(const Complex& lhs, const Complex& rhs) {
        double f = lhs.real * rhs.real;
        double o = lhs.real * rhs.imag;
        double i = lhs.imag * rhs.real;
        double l = lhs.imag * rhs.imag * -1.0;
        
        Complex result(f + l, o + i);
        return result;
        
    }

Complex operator/(const Complex& lhs, const Complex& rhs) { 
       	Complex conjugate(rhs.real, rhs.imag * -1.0);
       	Complex new_lhs = lhs * conjugate;
	double new_rhs = rhs.real * conjugate.real + -1.0 * rhs.imag * conjugate.imag;

	Complex result(new_lhs.real / new_rhs, new_lhs.imag / new_rhs);

            
	return result;
    }       


#endif









