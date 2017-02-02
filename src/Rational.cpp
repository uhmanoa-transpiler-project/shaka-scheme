#include "Rational.h"

Rational::int get_numerator() {
	return numer;
}

Rational::int get_denominator() {
	return denominator;
}

Rational::virtual Rational max(const Rational& other) const override {
	int this_numer = numer * other.denom;
	int other_numer = other.numer * denom;
	if (this_numer >= other_numer) {
		return Rational(numer, denom);
	}
	else {
		return Rational(other);
	}
}

Rational::virtual Rational min(const Rational& other) const override {
	int this_numer = numer * other.denom;
	int other_numer = other.numer * denom;
	if (this_numer <= other_numer) {
		return Rational(numer, denom);
	}
	else {
		return Rational(other);
	}
}

Rational::virtual Rational floor() const override {
	return Rational(floor(numer / denom), 1);
}

Rational::virtual Rational ceiling() const override {
	return Rational(ceil(numer / denom), 1);
}

Rational::virtual Rational truncate() const override {
	return Rational(trunc(numer / denom), 1);
}

Rational::virtual Rational round() const override {
	return Rational(round(numer / denom), 1);
}

Rational::virtual Rational operator+(const Rational& lhs, const Rational& rhs) const override {
	return Rational(lhs.numer * rhs.denom + rhs.numer * lhs.denom,
			lhs.denom * rhs.denom);
}

Rational::virtual Rational operator-(const Rational& lhs, const Rational& rhs) const override {
	return Rational(lhs.numer * rhs.denom - rhs.numer * lhs.denom,
			lhs.denom * rhs.denom);
}

Rational::virtual Rational operator*(const Rational& lhs, const Rational& rhs) const override {
	return Rational(lhs.numer * rhs.numer, lhs.denom * rhs.denom);
}

Rational::virtual Rational operator/(const Rational& lhs, const Rational& rhs) const override {
	return Rational(lhs.numer * rhs.denom, rhs.numer * lhs.denom);
}

Rational::virtual bool operator==(const Rational& lhs, const Rational& rhs) const override {
	return lhs.numer == rhs.numer && lhs.denom == rhs.denom;
}

Rational::virtual bool operator>(const Rational& lhs, const Rational& rhs) const override {
	lhs_numer = lhs.numer * rhs.denom;
	rhs_numer = rhs.numer * lhs.denom;
	return lhs_numer > rhs_numer;
}

Rational::virtual bool operator<(const Rational& lhs, const Rational& rhs) const override {
	return !(lhs > rhs) && !(lhs == rhs);
}

Rational::virtual bool operator>=(const Rational& lhs, const Rational& rhs) const override {
	return (lhs > rhs) || (lhs == rhs);

}

Rational::virtual bool operator<=(const Rational& lhs, const Rational& rhs) const override {
	return (lhs < rhs) || (lhs == rhs);
}

Rational::virtual bool operator!=(const Rational& lhs, const Rational& rhs) const override {
	return !(lhs == rhs);
}


