//
// Created by Billy Wooton on 11/29/17.
//

#ifndef SHAKA_SCHEME_RATIONAL_HPP
#define SHAKA_SCHEME_RATIONAL_HPP

namespace shaka {

class Real;

class Rational {
public:

  Rational(int num, int denom);
  Rational(const Rational& other) :
      numer(other.numer),
      denom(other.denom) {};

  /**
   * @brief Implicit type conversion operator for Rational -> Real
   * @return The Real number conversion for this Rational
   */
  operator Real();

  // getters for supporting unit testing
  int get_numerator() const;
  int get_denominator() const;

  // arithmetic operators
  friend Rational operator+(const Rational& lhs, const Rational& rhs);
  friend Rational operator-(const Rational& lhs, const Rational& rhs);
  friend Rational operator*(const Rational& lhs, const Rational& rhs);
  friend Rational operator/(const Rational& lhs, const Rational& rhs);

  // comparison operators
  friend bool operator==(const Rational& lhs, const Rational& rhs);
  friend bool operator>(const Rational& lhs, const Rational& rhs);
  friend bool operator<(const Rational& lhs, const Rational& rhs);
  friend bool operator>=(const Rational& lhs, const Rational& rhs);
  friend bool operator<=(const Rational& lhs, const Rational& rhs);
  friend bool operator!=(const Rational& lhs, const Rational& rhs);

private:

  int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
  }

  void reduce() {
    int divisor = gcd(numer, denom);
    numer /= divisor;
    denom /= divisor;
  }

  int numer, denom;

};

} // namespace shaka

#endif //SHAKA_SCHEME_RATIONAL_HPP
