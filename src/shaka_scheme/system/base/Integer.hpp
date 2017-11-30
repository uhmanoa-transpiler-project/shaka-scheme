//
// Created by Billy Wooton on 11/29/17.
//

#ifndef SHAKA_SCHEME_INTEGER_HPP
#define SHAKA_SCHEME_INTEGER_HPP

namespace shaka {

class Rational;
class Real;

class Integer {
public:

  Integer(const Integer& other) :
      value(other.value) {};
  Integer(int val) :
      value(val) {};

  /**
   * @brief Implicit type conversion operator for Integer -> Rational
   * Needed for interop between numeric subtypes in operator overloads
   * @return The Rational conversion for this Integer object
   */
  operator Rational();
  /**
   * @brief Implicit type conversion operator for Integer -> Real
   * Needed for interop between numeric subtypes in operator overloads
   * @return The Real conversion for this Integer object
   */
  operator Real();

  // arithmetic operators for Integers
  friend Integer operator+(const Integer& lhs, const Integer& rhs);
  friend Integer operator-(const Integer& lhs, const Integer& rhs);
  friend Integer operator*(const Integer& lhs, const Integer& rhs);
  friend Rational operator/(const Integer& lhs, const Integer& rhs);
  friend Integer operator|(const Integer& lhs, const Integer& rhs);
  friend Integer operator%(const Integer& lhs, const Integer& rhs);

  // comparison operators for Integers
  friend bool operator==(const Integer& lhs, const Integer& rhs);
  friend bool operator>(const Integer& lhs, const Integer& rhs);
  friend bool operator<(const Integer& lhs, const Integer& rhs);
  friend bool operator>=(const Integer& lhs, const Integer& rhs);
  friend bool operator<=(const Integer& lhs, const Integer& rhs);
  friend bool operator!=(const Integer& lhs, const Integer& rhs);

  int get_value() const;
private:
  int value;
};

} // namespace shaka
#endif //SHAKA_SCHEME_INTEGER_HPP
