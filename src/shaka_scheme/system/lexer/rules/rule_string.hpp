#ifndef SHAKA_SCHEME_RULE_STRING_HPP
#define SHAKA_SCHEME_RULE_STRING_HPP

#include "shaka_scheme/system/lexer/rules/common_rules.hpp"

namespace shaka {
namespace lexer {
namespace rules {

extern LexerRule double_quote;
extern LexerRule string_element;
extern LexerRule string_rule;

void init_rule_string();

} // namespace rules
} // namespace lexer
} // namespace shaka

#endif //SHAKA_SCHEME_RULE_BOOLEAN_HPP
