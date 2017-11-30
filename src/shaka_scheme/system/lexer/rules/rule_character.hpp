#ifndef SHAKA_SCHEME_RULE_CHARACTER_HPP
#define SHAKA_SCHEME_RULE_CHARACTER_HPP

#include "shaka_scheme/system/lexer/rules/common_rules.hpp"

namespace shaka {
namespace lexer {
namespace rules {

extern LexerRule character_name;
extern LexerRule character;

void init_rule_character();

} // namespace rules
} // namespace lexer
} // namespace shaka

#endif //SHAKA_SCHEME_RULE_CHARACTER_HPP
