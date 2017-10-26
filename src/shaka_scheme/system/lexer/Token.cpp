//
// Created by aytas on 10/25/2017.
//

#include "shaka_scheme/system/lexer/Token.hpp"

namespace shaka {

std::ostream& operator<<(std::ostream& out, Token rhs) {
  out << "Token(" << static_cast<int>(rhs.type) << ",\"" << rhs.str << "\")";
  return out;
}

bool operator==(const Token& lhs, const Token& rhs) {
  return (
      lhs.type == rhs.type &&
          lhs.str == rhs.str
  );
}

bool operator!=(const Token& lhs, const Token& rhs) {
  return !operator==(lhs, rhs);
}

} // namespace shaka
