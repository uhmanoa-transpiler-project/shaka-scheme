#ifndef VALUE_H
#define VALUE_H

#include "Integer.h"
#include <typeinfo>
#include <boost/variant.hpp>
#include <cassert>

namespace shaka {

using Value = boost::variant<Integer, Real, Rational>;
		
Value operator+(Value v1, Value v2) {
	if (v1.type() == typeid(Integer)) {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Integer>(v1) + boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Integer>(v1) + boost::get<Rational>(v2);
		}
		else {
			return boost::get<Integer>(v1) + boost::get<Real>(v2);
		}
	}
	else if (v1.type() == typeid(Rational)) {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Rational>(v1) + boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Rational>(v1) + boost::get<Rational>(v2);
		}
		else {
			return boost::get<Rational>(v1) + boost::get<Real>(v2);
		}
	}
	else {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Real>(v1) + boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Real>(v1) + boost::get<Rational>(v2);
		}
		else {
			return boost::get<Real>(v1) + boost::get<Real>(v2);
		}
	}
}

Value operator-(Value v1, Value v2) {
	if (v1.type() == typeid(Integer)) {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Integer>(v1) - boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Integer>(v1) - boost::get<Rational>(v2);
		}
		else {
			return boost::get<Integer>(v1) - boost::get<Real>(v2);
		}
	}
	else if (v1.type() == typeid(Rational)) {
		if (v2.type() == typeid(Integer)){
			return boost::get<Rational>(v1) - boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Rational>(v1) - boost::get<Rational>(v2);
		}
		else {
			return boost::get<Rational>(v1) - boost::get<Real>(v2);
		}
	}
	else {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Real>(v1) - boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Real>(v1) - boost::get<Rational>(v2);
		}
		else {
			return boost::get<Real>(v1) - boost::get<Real>(v2);
		}
	}
}

Value operator*(Value v1, Value v2) {
	if (v1.type() == typeid(Integer)) {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Integer>(v1) * boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Integer>(v1) * boost::get<Rational>(v2);
		}
		else {
			return boost::get<Integer>(v1) * boost::get<Real>(v2);}
	}
	else if (v1.type() == typeid(Rational)) {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Rational>(v1) * boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Rational>(v1) * boost::get<Rational>(v2);
		}
		else {
			return boost::get<Rational>(v1) * boost::get<Real>(v2);
		}
	}
	else {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Real>(v1) * boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Real>(v1) * boost::get<Rational>(v2);
		}
		else {
			return boost::get<Real>(v1) * boost::get<Real>(v2);
		}
	}
}

Value operator/(Value v1, Value v2) {
	if (v1.type() == typeid(Integer)) {
		if (v2.type() == typeid(Integer)) {
			/// @todo maybe put exception for division by 0
			assert(boost::get<Integer>(v2) != Integer(0));
			return boost::get<Integer>(v1) / boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			/// @todo maybe put exception for divisoin by 0
			assert(boost::get<Rational>(v2).get_numerator() != 0);
			return boost::get<Integer>(v1) / boost::get<Rational>(v2);
		}
		else {
			/// @todo maybe add exception for division by 0
			assert(boost::get<Real>(v2) != Real(0.0));
			return boost::get<Integer>(v1) / boost::get<Real>(v2);
		}
	}
	else if (v1.type() == typeid(Rational)) {
		if (v2.type() == typeid(Integer)) {
			/// @todo maybe put exception for division by 0
			assert(boost::get<Integer>(v2) != Integer(0));
			return boost::get<Rational>(v1) / boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			/// @todo maybe put exception for division by 0
			assert(boost::get<Rational>(v2).get_numerator() != 0);
			return boost::get<Rational>(v1) / boost::get<Rational>(v2);
		}
		else {
			/// @todo maybe put exception for division by 0
			assert(boost::get<Real>(v2) != Real(0.0));
			return boost::get<Rational>(v1) / boost::get<Real>(v2);
		}
	}
	else {
		if (v2.type() == typeid(Integer)) {
			/// @todo maybe add exception for division by 0
			assert(boost::get<Integer>(v2) != Integer(0));
			return boost::get<Real>(v1) / boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			/// @todo maybe add exception for division by 0
			assert(boost::get<Rational>(v2).get_numerator() != 0);
			return boost::get<Real>(v1) / boost::get<Rational>(v2);
		}
		else {
			/// @todo maybe add exception for division by 0
			assert(boost::get<Real>(v2) != Real(0.0));
			return boost::get<Real>(v1) / boost::get<Real>(v2);
		}
	}
}

bool value_eq_p(Value v1, Value v2) {
	if (v1.type() == typeid(Integer)) {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Integer>(v1) == boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Integer>(v1) == boost::get<Rational>(v2);
		}
		else {
			return boost::get<Integer>(v1) == boost::get<Real>(v2);
		}
	}
	else if (v1.type() == typeid(Rational)) {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Rational>(v1) == boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Rational>(v1) == boost::get<Rational>(v2);
		}
		else {
			return boost::get<Rational>(v1) == boost::get<Real>(v2);
		}
	}
	else {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Real>(v1) == boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Real>(v1) == boost::get<Rational>(v2);
		}
		else {
			return boost::get<Real>(v1) == boost::get<Real>(v2);
		}
	}
}


bool value_lt_p(Value v1, Value v2) {
	if (v1.type() == typeid(Integer)) {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Integer>(v1) < boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Integer>(v1) < boost::get<Rational>(v2);
		}
		else {
			return boost::get<Integer>(v1) < boost::get<Real>(v2);
		}
	}
	else if (v1.type() == typeid(Rational)) {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Rational>(v1) < boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Rational>(v1) < boost::get<Rational>(v2);
		}
		else {
			return boost::get<Rational>(v1) < boost::get<Real>(v2);
		}
	
	}
	else {
		if (v2.type() == typeid(Integer)) {
			return boost::get<Real>(v1) < boost::get<Integer>(v2);
		}
		else if (v2.type() == typeid(Rational)) {
			return boost::get<Real>(v1) < boost::get<Rational>(v2);
		}
		else {
			return boost::get<Real>(v1) < boost::get<Real>(v2);
		}
	}
}
} // namespace shaka
#endif
