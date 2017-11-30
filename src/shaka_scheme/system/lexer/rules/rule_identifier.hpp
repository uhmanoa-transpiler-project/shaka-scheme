//
// Created by aytas on 10/31/2017.
//

#ifndef SHAKA_SCHEME_RULE_IDENTIFIER_HPP
#define SHAKA_SCHEME_RULE_IDENTIFIER_HPP

#include "shaka_scheme/system/lexer/rules/common_rules.hpp"

#include <cctype>

namespace shaka {
namespace lexer {
namespace rules {

extern LexerRule special_initial;
extern LexerRule initial;
extern LexerRule explicit_sign;

extern LexerRule special_subsequent;

extern LexerRule subsequent;

extern LexerRule sign_subsequent;
extern LexerRule dot_subsequent;
extern LexerRule peculiar_identifier;

extern LexerRule symbol_element;

extern LexerRule identifier;

void init_rule_identifier();

} // namespace rules
} // namespace lexer
} // namespace shaka

#endif //SHAKA_SCHEME_RULE_IDENTIFIER_HPP
