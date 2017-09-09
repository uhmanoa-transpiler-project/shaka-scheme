#include "shaka_scheme/system/base/Boolean.hpp"

namespace shaka {

bool operator==(const Boolean& n1, const Boolean& n2) {
  return n1.value == n2.value;
}

bool operator!=(const Boolean& n1, const Boolean& n2) {
  return !(n1 == n2);
}

std::ostream& operator<<(std::ostream& lhs, const shaka::Boolean& rhs) {
  lhs << ((rhs.get_value()) ? "#t" : "#f");
  return lhs;
}

} // namespace shaka
