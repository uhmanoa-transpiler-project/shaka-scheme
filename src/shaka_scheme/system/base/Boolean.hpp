#ifndef SHAKA_CORE_BASE_BOOLEAN_H
#define SHAKA_CORE_BASE_BOOLEAN_H
#include <iostream>
namespace shaka {

class Boolean {
public:

  Boolean() : value(false) {}

  Boolean(bool v) : value(v) {}

  bool get_value() const { return value; }
  void set_value(bool v) { value = v; }

  // overload the == and != operator for Boolean
  friend bool operator==(const Boolean &n1, const Boolean &n2);
  // hint: == is already overloaded for std::string
  // != can be defined in terms of ==
  friend bool operator!=(const Boolean &n1, const Boolean &n2);

  friend std::ostream& operator<<(std::ostream& lhs, const shaka::Boolean& rhs);

private:
  bool value;
};

} // namespace shska
#endif // SHAKA_CORE_BASE_BOOLEAN_H
