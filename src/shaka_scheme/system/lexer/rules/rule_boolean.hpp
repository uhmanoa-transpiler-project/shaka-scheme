//
// Created by aytas on 10/31/2017.
//

#ifndef SHAKA_SCHEME_RULE_BOOLEAN_HPP
#define SHAKA_SCHEME_RULE_BOOLEAN_HPP

#include "shaka_scheme/system/lexer/rules/common_rules.hpp"

#include <cctype>

namespace shaka {
namespace lexer {
namespace rules {

LexerRule boolean_true = (make_terminal("#true") | make_terminal("#t"))
    /"boolean-true";

LexerRule boolean_false = (make_terminal("#false") | make_terminal("#f"))
  /"boolean-false";

LexerRule boolean = boolean_true | boolean_false;

} // namespace rules
} // namespace lexer
} // namespace shaka

#endif //SHAKA_SCHEME_RULE_BOOLEAN_HPP
