#ifndef SHAKA_SCHEME_RULE_TOKEN_HPP
#define SHAKA_SCHEME_RULE_TOKEN_HPP

#include "shaka_scheme/system/lexer/lexer_definitions.hpp"
#include "shaka_scheme/system/lexer/rules/rule_identifier.hpp"
#include "shaka_scheme/system/lexer/rules/rule_comment.hpp"
#include "shaka_scheme/system/lexer/rules/rule_string.hpp"
#include "shaka_scheme/system/lexer/rules/rule_boolean.hpp"
#include "shaka_scheme/system/lexer/rules/rule_character.hpp"
#include "shaka_scheme/system/lexer/rules/rule_number.hpp"
#include "shaka_scheme/system/lexer/rules/rule_comment.hpp"

namespace shaka {
namespace lexer {
namespace rules {

extern LexerRule dot;
extern LexerRule comma_atsign;
extern LexerRule comma;
extern LexerRule backtick;
extern LexerRule quote;
extern LexerRule bytevector_left;
extern LexerRule vector_left;
extern LexerRule paren_right;
extern LexerRule paren_left;
extern LexerRule datum_comment;

extern LexerRule directive;

extern LexerRule token;

extern LexerRule atmosphere;

extern LexerRule intertoken_space;

extern LexerRule scheme_lexer;

void init_rule_token();

} // namespace rules
} // namespace lexer
} // namespace shaka

#endif //SHAKA_SCHEME_RULE_TOKEN_HPP
