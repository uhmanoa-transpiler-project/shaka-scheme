#ifndef INTEGER_H
#define INTEGER_H
#include "Rational.h"
class Integer : public Rational {
public:
	~Integer() {}
	Integer(int v) : value(v) {}
	Integer(const Integer& i) : value(i.value) {}
	virtual Integer max(const Integer& i) const override {}
	virtual Integer min(const Integer& i) const override {}
	Integer gcd(const Integer& i) const {}
	Integer lcm(const Integer& i) const {}
	virtual Integer operator+(const Integer& lhs, const Integer& rhs) const override {}
	virtual Integer operator-(const Integer& lhs, const Integer& rhs) const override {}
	virtual Integer operator*(const Integer& lhs, const Integer& rhs) const override {}
	virtual Integer operator/(const Integer& lhs, const Integer& rhs) const override {}
	virtual bool operator==(const Integer& i) const override {}
	virtual bool >(const Integer& i) const override {}
	virtual bool <(const Integer& i) const override {}
	virtual bool >=(const Integer& i) const override {}
	virtual bool <=(const Integer& i) const override {}
	virtual bool !=(const Integer& i) const override {}	
private:
	int value;
};
#endif
