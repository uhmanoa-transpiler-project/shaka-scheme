#ifndef RATIONAL_H
#define RATIONAL_H
#include "Real.h"
class Rational : public Real {
public:
	// constructors and destructor
	~Rational() {}
	Rational(int n, int d) : numer(n), denom(d) {}
	Rational(Rational& r) : numer(r.numer), denom(r.denom) {}
	
	// getters
	int get_numerator() {}
	int get_denominator() {}
	
	// max and min builtins
	virtual Rational max(const Rational& other) const override {}
	virtual Rational min(const Rational& other) const override {}
	
	// rounding methods
	virtual Rational floor() const override {}
	virtual Rational ceiling() const override {}
	virtual Rational truncate() const override {}
	virtual Rational round() const override {}
	
	// arithmetic operators
	virtual Rational operator+(const Rational& lhs, const Rational& rhs) const override {}
	virtual Rational operator-(const Rational& lhs, const Rational& rhs) const override {}
	virtual Rational operator*(const Rational& lhs, const Rational& rhs) const override {}
	virtual Rational operator/(const Rational& lhs, const Rational& rhs) const override {}
	
	// comparison operators
	virtual bool operator==(const Rational& lhs, const Rational& rhs) const override {}
	virtual bool operator>(const Rational& lhs, const Rational& rhs) const override {}
	virtual bool operator<(const Rational& lhs, const Rational& rhs) const override {}
	virtual bool operator>=(const Rational& lhs, const Rational& rhs) const override {}
	virtual bool operator<=(const Rational& lhs, const Rational& rhs) const override {}
	virtual bool operator!=(const Rational& lhs, const Rational& rhs) const override {}
private:
	int numer, denom;
};
#endif
