#ifndef NUMBER_H
#define NUMBER_H

#include <cassert>
#include "Integer.h"

// Tagged union wrapper over all of the numeric types in our
// numeric tower: Complex, Real, Rational, and Integer
// The rest of the builtin numeric procedures will be built
// over this wrapper (i.e. anything that isn't an arithmetic or comparison operator)
class Number {
public:

	enum Type {
		COMPLEX,
		REAL,
		RATIONAL,
		INTEGER
	};

	Number(const Complex& value) : type(COMPLEX), value(value) {}
	Number(const Real& value) : type(REAL), value(value) {}
	Number(const Rational& value) : type(RATIONAL), value(value) {}
	Number(const Integer& value) : type(INTEGER), value(value) {}

	Type getType() const {return type;}
	Complex getComplex() const {
		assert(type == COMPLEX);
		return value.getComplex();
	}

	Real getReal() const {
		assert(type == REAL);
		return value.getReal();
	}

	Rational getRational() const {
		assert(type == RATIONAL);
		return value.getRational();
	}

	Integer getInteger() const {
		assert(type == INTEGER);
		return value.getInteger();
	}


private:
	union Value {
		Value(const Complex& value) : complexValue(value) {}
		Value(const Real& value) : realValue(value) {}
		Value(const Rational& value) : rationalValue(value) {}
		Value(const Integer& value) : integerValue(value) {}

		Complex getComplex() const {return complexValue;}
		Real getReal() const {return realValue;}
		Rational getRational() const {return rationalValue;}
		Integer getInteger() const {return integerValue;}

	private:
		Complex complexValue;
		Real realValue;
		Rational rationalValue;
		Integer integerValue;

	};

	Type type;
	Value value;
	
};


#endif
