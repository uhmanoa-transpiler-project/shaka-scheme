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

extern LexerRule boolean_true;

extern LexerRule boolean_false;

extern LexerRule boolean;

void init_rule_boolean();

} // namespace rules
} // namespace lexer
} // namespace shaka

#endif //SHAKA_SCHEME_RULE_BOOLEAN_HPP
