//
// Created by aytas on 11/1/2017.
//

#ifndef SHAKA_SCHEME_RULE_NUMBER_HPP
#define SHAKA_SCHEME_RULE_NUMBER_HPP

#include "shaka_scheme/system/lexer/rules/common_rules.hpp"

#include <cctype>

namespace shaka {
namespace lexer {
namespace rules {

extern LexerRule sign;
extern LexerRule whole_number;
extern LexerRule integer;
extern LexerRule real;
extern LexerRule rational;
extern LexerRule number;

void init_rule_number();

} // namespace rules
} // namespace lexer
} // namespace shaka


#endif //SHAKA_SCHEME_RULE_NUMBER_HPP
