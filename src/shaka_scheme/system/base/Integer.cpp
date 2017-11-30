//
// Created by Billy Wooton on 11/29/17.
//

#include "shaka_scheme/system/base/Integer.hpp"
#include "shaka_scheme/system/base/Rational.hpp"
#include "shaka_scheme/system/base/Real.hpp"

namespace shaka {

Integer::operator Rational() {
  Rational result(value, 1);
  return result;
}

Integer::operator Real() {
  Real result((double) value);
  return result;
}

int Integer::get_value() const {
  return value;
}

Integer operator+(const Integer& lhs, const Integer& rhs) {
  Integer result(lhs.value + rhs.value);
  return result;
}

Integer operator-(const Integer& lhs, const Integer& rhs) {
  Integer result(lhs.value - rhs.value);
  return result;
}

Integer operator*(const Integer& lhs, const Integer& rhs) {
  Integer result(lhs.value * rhs.value);
  return result;
}

Rational operator/(const Integer& lhs, const Integer& rhs) {
  Rational result(lhs.value, rhs.value);
  return result;
}

Integer operator|(const Integer& lhs, const Integer& rhs) {
  Integer result(lhs.value / rhs.value);
  return result;
}

Integer operator%(const Integer& lhs, const Integer& rhs) {
  Integer result(lhs.value % rhs.value);
  return result;
}

bool operator==(const Integer& lhs, const Integer& rhs) {
  return lhs.value == rhs.value;
}

bool operator>(const Integer& lhs, const Integer& rhs) {
  return lhs.value > rhs.value;
}

bool operator<(const Integer& lhs, const Integer& rhs) {
  return lhs.value < rhs.value;
}

bool operator>=(const Integer& lhs, const Integer& rhs) {
  return lhs.value >= rhs.value;
}

bool operator<=(const Integer& lhs, const Integer& rhs) {
  return lhs.value <= rhs.value;
}

bool operator!=(const Integer& lhs, const Integer& rhs) {
  return lhs.value != rhs.value;
}

} // namespace shaka