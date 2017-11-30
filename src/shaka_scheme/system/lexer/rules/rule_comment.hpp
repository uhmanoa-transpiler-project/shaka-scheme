//
// Created by aytas on 10/31/2017.
//

#ifndef SHAKA_SCHEME_RULE_COMMENT_HPP
#define SHAKA_SCHEME_RULE_COMMENT_HPP

#include "shaka_scheme/system/lexer/rules/common_rules.hpp"

namespace shaka {
namespace lexer {
namespace rules {

// line comment
extern LexerRule line_comment;

// nested comment
extern LexerRule nested_comment_left;
extern LexerRule nested_comment_right;
extern LexerRule nested_comment_delimiter;
extern LexerRule comment_text;

extern LexerRule nested_comment;

extern LexerRule comment;

void init_rule_comment();

} // namespace rules
} // namespace lexer
} // namespace shaka

#endif //SHAKA_SCHEME_RULE_COMMENT_HPP
