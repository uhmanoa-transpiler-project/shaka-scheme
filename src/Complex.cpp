#include "Complex.h"

Complex::virtual Complex operator+(const Complex& lhs, const Complex& rhs) const override {
	Complex result(lhs.real + rhs.real, lhs.imag + rhs.imag);
	return result;
}

Complex::virtual Complex operator-(const Complex& lhs, const Complex& rhs) const override {
        Complex result(lhs.real - rhs.real, lhs.imag - rhs.imag);
        return result;
}


Complex::virtual Complex operator*(const Complex& lhs, const Complex& rhs) const override {
        double f = lhs.real * rhs.real;
        double o = lhs.real * rhs.imag;
        double i = lhs.imag * rhs.real;
        double l = lhs.imag * rhs.imag * -1;
        
        Complex result(f + l, o + i);
        return result;
        
    }
Complex::virtual Complex operator/(const Complex& lhs, const Complex& rhs) const override {
        Complex conjugate(rhs.real, rhs.imag * -1);
        Complex new_numer(lhs * conjugate);
        double new_denom = (rhs.real * rhs.real + rhs.imag * rhs.imag);
        
        Complex result(new_numer.real / new_denom, new_numer.imag / new_denom);
        return result;
            
    }       


Complex::virtual bool operator==(const Complex& lhs, const Complex& rhs) const override {
        return (lhs.real == rhs.real) && (lhs.imag == rhs.imag);
    }
