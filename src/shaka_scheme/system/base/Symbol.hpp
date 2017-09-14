#ifndef SHAKA_SCHEME_SYMBOL_H
#define SHAKA_SCHEME_SYMBOL_H

#include <string>

namespace shaka {

/**
 * @brief Represents a symbol within Shaka Scheme.
 */
class Symbol {
public:

  /**
   * @brief Default constructor for Symbol to empty string.
   */
  Symbol() :
    value("") {}

  /**
   * @brief Constructs a Symbol from a string.
   * @param v The string to construct from.
   */
  Symbol(const std::string& v) :
      value(v) {}

  friend void swap (shaka::Symbol& lhs, shaka::Symbol& rhs) {
    using std::swap;

    swap(lhs.value, rhs.value);
  }

  shaka::Symbol operator= (shaka::Symbol other) {
    shaka::Symbol temp(other);
    swap(*this, other);

    return *this;
  }

  const std::string get_value() const { return value; }
  // overload the == and != operator for Symbol
  friend bool operator==(const Symbol& n1, const Symbol& n2);
  // hint: == is already overloaded for std::string
  // != can be defined in terms of ==
  friend bool operator!=(const Symbol& n1, const Symbol& n2);
  friend bool operator<(const Symbol& n1, const Symbol& n2);
  friend bool operator<=(const Symbol& n1, const Symbol& n2);
  friend bool operator>(const Symbol& n1, const Symbol& n2);
  friend bool operator>=(const Symbol& n1, const Symbol& n2);

private:
  std::string value;
};

std::ostream& operator<<(std::ostream& lhs, shaka::Symbol rhs);

} // namespace shaka
#endif // SHAKA_SCHEME_SYMBOL_H
