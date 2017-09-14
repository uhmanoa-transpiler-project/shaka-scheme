#include "shaka_scheme/system/base/String.hpp"

namespace shaka {

std::ostream& operator<<(std::ostream& lhs, const shaka::String& rhs) {
  for (auto it : rhs.get_string()) {
    lhs << it;
  }
  return lhs;
}

} // namespace shaka
