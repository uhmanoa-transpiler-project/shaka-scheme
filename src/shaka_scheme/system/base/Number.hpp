//
// Created by Billy Wooton on 11/29/17.
//

#ifndef SHAKA_SCHEME_NUMBER_HPP
#define SHAKA_SCHEME_NUMBER_HPP

#include "shaka_scheme/system/base/Integer.hpp"
#include "shaka_scheme/system/base/Real.hpp"
#include "shaka_scheme/system/base/Rational.hpp"
#include <iostream>

namespace shaka {

class Integer;
class Rational;
class Real;

class Number {

public:

  enum class NumberType : int {
    INTEGER = 0,
    RATIONAL,
    REAL
  };

private:

  NumberType type_tag;

  union {
    shaka::Integer integer;
    shaka::Rational rational;
    shaka::Real real;
  };

public:

  ~Number();
  Number();
  Number(const Number& other);

  Number(const Integer& i);
  Number(const Rational& r);
  Number(const Real& r);

  Number(int v);
  Number(double v);
  Number(int n, int d);

  template<typename T>
  T get() const;

  NumberType get_type() const {
    return this->type_tag;
  }

  // arithmetic operators R7RS 6.2.6
  friend Number operator+(const Number& n1, const Number& n2);
  friend Number operator-(const Number& n1, const Number& n2);
  friend Number operator*(const Number& n1, const Number& n2);
  friend Number operator/(const Number& n1, const Number& n2);
  friend Number operator|(const Number& n1, const Number& n2);
  friend Number operator%(const Number& n1, const Number& n2);

  // comparison operators R7RS 6.2.6
  friend bool operator==(const Number& n1, const Number& n2);
  friend bool operator!=(const Number& n1, const Number& n2);
  friend bool operator>(const Number& n1, const Number& n2);
  friend bool operator<(const Number& n1, const Number& n2);
  friend bool operator>=(const Number& n1, const Number& n2);
  friend bool operator<=(const Number& n1, const Number& n2);

  friend std::ostream& operator<< (std::ostream& lhs, const Number& rhs);

};

} // namespace shaka

#endif //SHAKA_SCHEME_NUMBER_HPP
