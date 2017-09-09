#include "shaka_scheme/system/base/Symbol.hpp"

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

std::ostream& operator<<(std::ostream& lhs, shaka::Symbol rhs) {
  lhs << rhs.get_value();
  return lhs;
}

} // namespace shaka
