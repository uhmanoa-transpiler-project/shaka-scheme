#include "shaka_scheme/system/lexer/LexInfo.hpp"

namespace shaka {

bool operator==(const LexInfo& left, const LexInfo& right) {
  return left.line == right.line && left.col == right.col && left.pos ==
      right.pos && left.module_name == right.module_name;
}

bool operator!=(const LexInfo& left, const LexInfo& right) {
  return !(left == right);
}

} // namespace shaka