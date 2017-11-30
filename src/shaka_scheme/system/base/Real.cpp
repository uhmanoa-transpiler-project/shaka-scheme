//
// Created by Billy Wooton on 11/29/17.
//
#include "shaka_scheme/system/base/Real.hpp"
#include "shaka_scheme/system/base/Integer.hpp"
#include "shaka_scheme/system/base/Rational.hpp"


namespace shaka {

double Real::get_value() const{
  return value;
}

Real operator+(const Real& lhs, const Real& rhs) {
  Real result(lhs.value + rhs.value);
  return result;
}

Real operator-(const Real& lhs, const Real& rhs) {
  Real result(lhs.value - rhs.value);
  return result;
}

Real operator*(const Real& lhs, const Real& rhs) {
  Real result(lhs.value * rhs.value);
  return result;
}

Real operator/(const Real& lhs, const Real& rhs) {
  Real result(lhs.value / rhs.value);
  return result;
}

bool operator==(const Real& lhs, const Real& rhs) {
  return lhs.value == rhs.value;
}

bool operator>(const Real& lhs, const Real& rhs) {
  return lhs.value > rhs.value;
}

bool operator<(const Real& lhs, const Real& rhs) {
  return lhs.value < rhs.value;
}

bool operator>=(const Real& lhs, const Real& rhs) {
  return lhs.value >= rhs.value;
}

bool operator<=(const Real& lhs, const Real& rhs) {
  return lhs.value <= rhs.value;
}

bool operator!=(const Real& lhs, const Real& rhs) {
  return lhs.value != rhs.value;
}
}

