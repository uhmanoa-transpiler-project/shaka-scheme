#include "shaka_scheme/system/base/Symbol.hpp"

#include <iostream>

namespace shaka {

bool operator<(const Symbol& n1, const Symbol& n2) {
  return n1.value < n2.value;
}

bool operator<=(const Symbol& n1, const Symbol& n2) {
  return n1.value <= n2.value;
}

bool operator>(const Symbol& n1, const Symbol& n2) {
  return n1.value > n2.value;
}

bool operator>=(const Symbol& n1, const Symbol& n2) {
  return n1.value >= n2.value;
}

bool operator==(const Symbol& n1, const Symbol& n2) {
  return n1.value == n2.value;
}

bool operator!=(const Symbol& n1, const Symbol& n2) {
  return !(n1 == n2);
}

std::ostream& operator<<(std::ostream& lhs, const shaka::Symbol& rhs) {
  bool is_escaped = false;
  if (rhs.get_value().find_first_of(" \t\n\r") != std::string::npos) {
    is_escaped = true;
  }
  if (is_escaped) { lhs << "|"; }
  lhs << rhs.get_value();
  if (is_escaped) { lhs << "|"; }
  return lhs;
}

} // namespace shaka
