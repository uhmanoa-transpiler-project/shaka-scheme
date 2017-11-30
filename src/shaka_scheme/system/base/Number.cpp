//
// Created by Billy Wooton on 11/29/17.
//

#include "shaka_scheme/system/base/Number.hpp"
#include "shaka_scheme/system/exceptions/TypeException.hpp"


namespace shaka {

Number::~Number() {

  if (this->type_tag == shaka::Number::NumberType::INTEGER) {
    this->integer.~Integer();
  }
  else if (this->type_tag == shaka::Number::NumberType::RATIONAL) {
    this->rational.~Rational();
  }
  else {
    this->real.~Real();
  }

}

Number::Number() {
  new(&integer) shaka::Integer(0);
  this->type_tag = NumberType::INTEGER;
}

Number::Number(const Number& other) {
  if (other.get_type() == Number::NumberType::INTEGER) {
    new(&integer) shaka::Integer(other.integer);
  }
  else if (other.get_type() == Number::NumberType::RATIONAL) {
    new(&rational) shaka::Rational(other.rational);
  }
  else {
    new(&real) shaka::Real(other.real);
  }

  this->type_tag = other.type_tag;
}

Number::Number(const Integer& i) {
  new(&integer) shaka::Integer(i);
  this->type_tag = NumberType::INTEGER;
}

Number::Number(const Rational& r) {
  new(&rational) shaka::Rational(r);
  this->type_tag = NumberType::RATIONAL;
}

Number::Number(const Real& r) {
  new(&real) shaka::Real(r);
  this->type_tag = NumberType::REAL;
}

Number::Number(int v) {
  new(&integer) shaka::Integer(v);
  this->type_tag = Number::NumberType::INTEGER;
}

Number::Number(double v) {
  new(&real) shaka::Real(v);
  this->type_tag = Number::NumberType::REAL;
}

Number::Number(int n, int d) {
  new(&rational) shaka::Rational(n, d);
  this->type_tag = Number::NumberType::RATIONAL;
}

template<>
shaka::Integer shaka::Number::get<shaka::Integer>() const {
  if (this->type_tag != Number::NumberType::INTEGER) {
    throw shaka::TypeException(246, "Could not get Integer from Number");
  }
  return this->integer;
}

template<>
shaka::Rational shaka::Number::get<shaka::Rational>() const {
  if (this->type_tag != Number::NumberType::RATIONAL) {
    throw shaka::TypeException(246, "Could not get Rational from Number");
  }
  return this->rational;
}

template<>
shaka::Real shaka::Number::get<shaka::Real>() const {
  if (this->type_tag != Number::NumberType::REAL) {
    throw shaka::TypeException(246, "Could not get Real from Number");
  }
  return this->real;
}


Number operator+(const Number& n1, const Number& n2) {
  if (n1.get_type() == Number::NumberType::INTEGER) {
    Integer i1 = n1.get<Integer>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return i1 + n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return i1 + n2.get<Rational>();
    }
    else {
      return i1 + n2.get<Real>();
    }
  }
  else if (n1.get_type() == Number::NumberType::RATIONAL) {
    Rational r1 = n1.get<Rational>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return r1 + n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return r1 + n2.get<Rational>();
    }
    else {
      return r1 + n2.get<Real>();
    }
  }
  else {
    Real r1 = n1.get<Real>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return r1 + n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return r1 + n2.get<Rational>();
    }
    else {
      return r1 + n2.get<Real>();
    }
  }
}


Number operator-(const Number& n1, const Number& n2) {
  if (n1.get_type() == Number::NumberType::INTEGER) {
    Integer i1 = n1.get<Integer>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return i1 - n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return i1 - n2.get<Rational>();
    }
    else {
      return i1 - n2.get<Real>();
    }
  }
  else if (n1.get_type() == Number::NumberType::RATIONAL) {
    Rational r1 = n1.get<Rational>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return r1 - n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return r1 - n2.get<Rational>();
    }
    else {
      return r1 - n2.get<Real>();
    }
  }
  else {
    Real r1 = n1.get<Real>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return r1 - n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return r1 - n2.get<Rational>();
    }
    else {
      return r1 - n2.get<Real>();
    }
  }
}
Number operator*(const Number& n1, const Number& n2) {
  if (n1.get_type() == Number::NumberType::INTEGER) {
    Integer i1 = n1.get<Integer>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return i1 * n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return i1 * n2.get<Rational>();
    }
    else {
      return i1 * n2.get<Real>();
    }
  }
  else if (n1.get_type() == Number::NumberType::RATIONAL) {
    Rational r1 = n1.get<Rational>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return r1 * n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return r1 * n2.get<Rational>();
    }
    else {
      return r1 * n2.get<Real>();
    }
  }
  else {
    Real r1 = n1.get<Real>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return r1 * n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return r1 * n2.get<Rational>();
    }
    else {
      return r1 * n2.get<Real>();
    }
  }
}
Number operator/(const Number& n1, const Number& n2) {
  if (n1.get_type() == Number::NumberType::INTEGER) {
    Integer i1 = n1.get<Integer>();
    if (n2.get_type() == Number::NumberType::INTEGER) {

      Integer i2 = n2.get<Integer>();
      if (i2 == Integer(0)) {
        throw BaseException(0, "Cannot divide by zero");
      }
      return i1 / i2;
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      Rational r2 = n2.get<Rational>();

      if (r2.get_numerator() == 0) {
        throw BaseException(0, "Cannot divide by zero");
      }
      return i1 / r2;
    }
    else {

      Real r2 = n2.get<Real>();

      if (r2 == Real(0)) {
        throw BaseException(0, "Cannot divide by zero");
      }
      return i1 / r2;
    }
  }
  else if (n1.get_type() == Number::NumberType::RATIONAL) {
    Rational r1 = n1.get<Rational>();

    if (n2.get_type() == Number::NumberType::INTEGER) {
      Integer i2 = n2.get<Integer>();

      if (i2 == Integer(0)) {
        throw BaseException(0, "Cannot divide by zero");
      }
      return r1 / i2;
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      Rational r2 = n2.get<Rational>();

      if (r2.get_numerator() == 0) {
        throw BaseException(0, "Cannot divide by zero");
      }
      return r1 / r2;
    }
    else {
      Real r2 = n2.get<Real>();

      if (r2 == Real(0)) {
        throw BaseException(0, "Cannot divide by zero");
      }

      return r1 / r2;
    }
  }
  else {
    Real r1 = n1.get<Real>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      Integer i2 = n2.get<Integer>();

      if (i2 == Integer(0)) {
        throw BaseException(0, "Cannot divide by zero");
      }
      return r1 / i2;
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
     Rational r2 = n2.get<Rational>();

      if (r2.get_numerator() == 0) {
        throw BaseException(0, "Cannot divide by zero");
      }
      return r1 / r2;
    }
    else {
      Real r2 = n2.get<Real>();

      if (r2 == Real(0)) {
        throw BaseException(0, "Cannot divide by zero");
      }
      return r1 / r2;
    }
  }
}
Number operator|(const Number& n1, const Number& n2) {
  if (n1.get_type() == Number::NumberType::REAL
      || n1.get_type() == Number::NumberType::RATIONAL
      || n2.get_type() == Number::NumberType::REAL
      || n2.get_type() == Number::NumberType::RATIONAL) {
    throw TypeException(117, "Invalid operands to integer division");
  }

  return n1.get<Integer>() | n2.get<Integer>();
}
Number operator%(const Number& n1, const Number& n2) {
  if (n1.get_type() == Number::NumberType::REAL
      || n1.get_type() == Number::NumberType::RATIONAL
      || n2.get_type() == Number::NumberType::REAL
      || n2.get_type() == Number::NumberType::RATIONAL) {
    throw TypeException(117, "Invalid operands to modulus");
  }
  return n1.get<Integer>() % n2.get<Integer>();
}


bool operator==(const Number& n1, const Number& n2) {
  if (n1.get_type() == Number::NumberType::INTEGER) {
    Integer i1 = n1.get<Integer>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      Integer i2 = n2.get<Integer>();
      return i1 == i2;
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      Rational r2 = n2.get<Rational>();
      return i1 == r2;
    }
    else {
      return i1 == n2.get<Real>();
    }
  }
  else if (n1.get_type() == Number::NumberType::RATIONAL) {
    Rational r1 = n1.get<Rational>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return r1 == n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return r1 == n2.get<Rational>();
    }
    else {
      return r1 == n2.get<Real>();
    }
  }
  else {
    Real r1 = n1.get<Real>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return r1 == n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return r1 == n2.get<Rational>();
    }
    else {
      return r1 == n2.get<Real>();
    }
  }
}

bool operator<(const Number& n1, const Number& n2) {
  if (n1.get_type() == Number::NumberType::INTEGER) {
    Integer i1 = n1.get<Integer>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      Integer i2 = n2.get<Integer>();
      return i1 < i2;
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      Rational r2 = n2.get<Rational>();
      return i1 < r2;
    }
    else {
      return i1 < n2.get<Real>();
    }
  }
  else if (n1.get_type() == Number::NumberType::RATIONAL) {
    Rational r1 = n1.get<Rational>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return r1 < n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return r1 < n2.get<Rational>();
    }
    else {
      return r1 < n2.get<Real>();
    }
  }
  else {
    Real r1 = n1.get<Real>();
    if (n2.get_type() == Number::NumberType::INTEGER) {
      return r1 < n2.get<Integer>();
    }
    else if (n2.get_type() == Number::NumberType::RATIONAL) {
      return r1 < n2.get<Rational>();
    }
    else {
      return r1 < n2.get<Real>();
    }
  }
}

bool operator!=(const Number& n1, const Number& n2) {
  return !(n1 == n2);
}
bool operator>(const Number& n1, const Number& n2) {
  return !(n1 == n2 || n1 < n2);
}
bool operator>=(const Number& n1, const Number& n2) {
  return n1 > n2 || n1 == n2;
}
bool operator<=(const Number& n1, const Number& n2) {
  return n1 < n2 || n1 == n2;
}

std::ostream& operator<< (std::ostream& lhs, const Number& rhs) {
  if (rhs.get_type() == Number::NumberType::INTEGER) {
    lhs << rhs.get<Integer>().get_value();
  }
  else if (rhs.get_type() == Number::NumberType::RATIONAL) {
    Rational r = rhs.get<Rational>();
    lhs << r.get_numerator() << '/' << r.get_denominator();
  }
  else if (rhs.get_type() == Number::NumberType::REAL) {
    lhs << rhs.get<Real>().get_value();
  }
  else {
    throw TypeException(117, "Number.<<: Invalid variant type");
  }
  return lhs;
}






} // namespace shaka