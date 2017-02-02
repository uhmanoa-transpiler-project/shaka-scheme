#ifndef INUMBER_H
#define INUMBER_H

#include <string>

class Number {
public:
	virtual Number operator+(const Number& lhs, const Number& rhs) const = 0;
	virtual Number operator-(const Number& lhs, const Number& rhs) const = 0;
	virtual Number operator*(const Number& lhs, const Number& rhs) const = 0;
	virtual Number operator/(const Number& lhs, const Number& rhs) const = 0;

	virtual bool operator==(const Number& lhs, const Number& rhs) const = 0;
	
	virtual std::string to_string() const = 0;
	virtual ~INumber() {};
};
#endif
