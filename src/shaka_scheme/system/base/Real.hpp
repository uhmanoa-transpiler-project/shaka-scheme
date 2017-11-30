//
// Created by Billy Wooton on 11/29/17.
//

#ifndef SHAKA_SCHEME_REAL_HPP
#define SHAKA_SCHEME_REAL_HPP

namespace shaka {

class Real {

public:

  Real(double val) : value(val) {}
  Real(const Real& other) : value(other.value) {}

  // arithmetic operators
  friend Real operator+(const Real& lhs, const Real& rhs);
  friend Real operator-(const Real& lhs, const Real& rhs);
  friend Real operator*(const Real& lhs, const Real& rhs);
  friend Real operator/(const Real& lhs, const Real& rhs);

  // comparison operators
  friend bool operator==(const Real& lhs, const Real& rhs);
  friend bool operator>(const Real& lhs, const Real& rhs);
  friend bool operator<(const Real& lhs, const Real& rhs);
  friend bool operator>=(const Real& lhs, const Real& rhs);
  friend bool operator<=(const Real& lhs, const Real& rhs);
  friend bool operator!=(const Real& lhs, const Real& rhs);

  double get_value() const;




private:

  double value;

};

} // namespace shaka

#endif //SHAKA_SCHEME_REAL_HPP
