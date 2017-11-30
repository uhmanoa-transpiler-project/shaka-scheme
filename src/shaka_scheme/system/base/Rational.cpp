//
// Created by Billy Wooton on 11/29/17.
//

#include "shaka_scheme/system/base/Rational.hpp"
#include "shaka_scheme/system/base/Real.hpp"
#include "shaka_scheme/system/exceptions/BaseException.hpp"

namespace shaka {

Rational::Rational(int num, int denom) : numer(num),
                                         denom(denom)
{
  if (this->denom == 0) {
    throw BaseException(117, "Rational cannot have zero denominator");
  }

  if (this->denom < 0) {
    this->denom = -this->denom;
    numer = -numer;
  }

  this->reduce();
}

Rational::operator Real() {
  Real result((double) numer / (double) denom);
  return result;
}

int Rational::get_numerator() const {
  return numer;
}

int Rational::get_denominator() const {
  return denom;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
  double new_numer = lhs.numer * rhs.denom + rhs.numer * lhs
      .denom;
  double new_denom = lhs.denom * rhs.denom;
  Rational result(new_numer, new_denom);
  return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
  double new_numer = lhs.numer * rhs.denom - rhs.numer * lhs.denom;
  double new_denom = lhs.denom * rhs.denom;
  Rational result(new_numer, new_denom);
  return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
  Rational result(lhs.numer * rhs.numer, lhs.denom * rhs.denom);
  return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
  Rational result(lhs.numer * rhs.denom, lhs.denom * rhs.numer);
  return result;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
  if (lhs.denom == rhs.denom) {
    return lhs.numer == rhs.numer;
  }
  else {
    int left_numer = lhs.numer * rhs.denom;
    int right_numer = rhs.numer * lhs.denom;
    return left_numer == right_numer;
  }
}

bool operator>(const Rational& lhs, const Rational& rhs) {
  if (lhs.denom == rhs.denom) {
    return lhs.numer > rhs.numer;
  }
  else {
    int left_numer = lhs.numer * rhs.denom;
    int right_numer = rhs.numer * lhs.denom;
    return left_numer > right_numer;
  }
}

bool operator<(const Rational& lhs, const Rational& rhs) {
  return !(lhs == rhs) && !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
  return (lhs > rhs) || (lhs == rhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
  return (lhs < rhs) || (lhs == rhs);
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
  return !(lhs == rhs);
}


}