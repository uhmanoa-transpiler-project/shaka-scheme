#include "Real.h"

Real::virtual Real max(const Real& r) const {
	if (value >= r.value) {
		return Real(value);
	}
	else {
		return Real(r.value)
	}
}

Real::virtual Real min(const Real& r) const {
	if (value <= r.value) {
		return Real(value);
	}
	else {
		return Real(r.value);
	}
}

Real::virtual Real abs() const {
	return Real(abs(value));
}

Real::virtual Real truncate() const {
	return Real(trunc(value));
}

Real::virtual Real floor() const {
	return Real(floor(value));
}

Real::virtual Real ceiling() const {
	return Real(ceil(value));
}

Real::virtual Real round() const {
	return Real(round(value));
}

Real::virtual Real operator+(const Real& lhs, const Real& rhs) const override {
	return Real(lhs.value + rhs.value);
}

Real::virtual Real operator-(const Real& lhs, const Real& rhs) const override {
	return Real(lhs.value - rhs.value);
}

Real::virtual Real operator*(const Real& lhs, const Real& rhs) const override {
	return Real(lhs.value * rhs.value);
}

Real::virtual Real operator/(const Real& lhs, const Real& rhs) const override {
	return Real(lhs.value / rhs.value);
}

Real::virtual bool operator==(const Real& lhs, const Real& rhs) const override {
	return lhs.value == rhs.value;
}

Real::virtual bool operator>(const Real& lhs, const Real& rhs) const override {
	return lhs.value > rhs.value;
}

Real::virtual bool operator<(const Real& lhs, const Real& rhs) const override {
	return lhs.value < rhs.value;
}

Real::virtual bool operator!=(const Real& lhs, const Real& rhs) const override {
	return lhs.value != rhs.value;
}

Real::virtual bool operator>=(const Real& lhs, const Real& rhs) const override {
	return lhs.value >= rhs.value;
}

Real::virtual bool operator<=(const Real& lhs, const Real& rhs) const override {
	return lhs.value <= rhs.value;

}


