#ifndef REAL_H
#define REAL_H
#include "Complex.h"
#include <cmath>
class Real : public Complex {
public:
	Real(double v) : value(v) {}
	Real(Real& r) : value(r.value) {}
	~Real() {}
	virtual Real max(const Real& r) const {}
	virtual Real min(const Real& r) const {}
	
	virtual Real abs() const {}
	virtual Real truncate() const {}
	virtual Real floor() const {}
	virtual Real ceiling() const {}
	virtual Real round() const {}
	virtual Real operator+(const Real& lhs, const Real& rhs) const override {}
	virtual Real operator-(const Real& lhs, const Real& rhs) const override {}
	virtual Real operator*(const Real& lhs, const Real& rhs) const override {}
	virtual Real operator/(const Real& lhs, const Real& rhs) const override {}
	virtual bool operator==(const Real& lhs, const Real& rhs) const override {}
	virtual bool operator>(const Real& lhs, const Real& rhs) const {}
	virtual bool operator<(const Real& lhs, const Real& rhs) const {}
	virtual bool operator!=(const Real& lhs, const Real& rhs) const {}
	virtual bool operator>=(const Real& lhs, const Real& rhs) const {}
	virtual bool operator<=(const Real& lhs, const Real& rhs) const {}
private:
	double value;
};
#endif
