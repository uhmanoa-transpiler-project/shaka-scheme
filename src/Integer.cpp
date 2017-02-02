#include "Integer.h"

Integer::virtual Integer max(const Integer& i) const override {
	if (value >= i.value) {
		return Integer(value);
	}
	else {
		return Integer(i)
	}
}

Integer::virtual Integer min(const Integer& i) const override {
	if (value <= i.value) {
		return Integer(value);
	}
	else {
		return Integer(i)
	}
}

Integer::Integer gcd(const Integer& i) const {
	int a = value;
	int b = i.value;
	int temp = 0;

	while (b > 0) {
		temp = b;
		b = a % b;
		a = temp;
	}
	return Integer(a);
}

Integer::Integer lcm(const Integer& i) const {
	Integer product((*this) * i);
	Integer gcd(this->gcd(i));
	return Integer(product/gcd);
}

Integer::virtual Integer operator+(const Integer& lhs, const Integer& rhs) const override {
	return Integer(lhs.value + rhs.value);
}

Integer::virtual Integer operator-(const Integer& lhs, const Integer& rhs) const override {
	return Integer(lhs.value - rhs.value);
}

Integer::virtual Integer operator*(const Integer& lhs, const Integer& rhs) const override {
	return Integer(lhs.value * rhs.value);
}

Integer::virtual Integer operator/(const Integer& lhs, const Integer& rhs) const override {
	return Integer(lhs.value / rhs.value);
}

Integer::virtual bool operator==(const Integer& lhs, const Integer& rhs) const override {
	return lhs.value == rhs.value;
}

Integer::virtual bool operator>(const Integer& lhs, const Integer& rhs) const override {
	return lhs.value > rhs.value;
}

Integer::virtual bool operator<(const Integer& lhs, const Integer& rhs) const override {
	return lhs.value < rhs.value;
}

Integer::virtual bool operator>=(const Integer& lhs, const Integer& rhs) const override {
	return lhs.value >= rhs.value;
}

Integer::virtual bool operator<=(const Integer& lhs, const Integer& rhs) const override {
	return lhs.value <= rhs.value;
}

Integer::virtual bool operator!=(const Integer& lhs, const Integer& rhs) const override {
	return lhs.value != rhs.value;
}


