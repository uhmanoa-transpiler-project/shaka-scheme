//
// Created by aytas on 10/23/2017.
//

#ifndef SHAKA_SCHEME_SYNTAXINFO_HPP
#define SHAKA_SCHEME_SYNTAXINFO_HPP

#include "shaka_scheme/system/lexer/LexInfo.hpp"

#include <string>
#include <set>

namespace shaka {

struct SyntaxInfo {
  LexInfo lex_info;
  std::set<std::size_t> scopes;
  int phase_level;
};

} // namespace shaka

#endif //SHAKA_SCHEME_SYNTAXINFO_HPP
