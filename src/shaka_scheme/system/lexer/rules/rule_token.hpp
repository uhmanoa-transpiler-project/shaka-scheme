//
// Created by aytas on 10/31/2017.
//

#ifndef SHAKA_SCHEME_RULE_TOKEN_HPP
#define SHAKA_SCHEME_RULE_TOKEN_HPP

#include "shaka_scheme/system/lexer/lexer_definitions.hpp"
#include "shaka_scheme/system/lexer/rules/rule_identifier.hpp"
#include "shaka_scheme/system/lexer/rules/rule_comment.hpp"
#include "shaka_scheme/system/lexer/rules/rule_string.hpp"
#include "shaka_scheme/system/lexer/rules/rule_boolean.hpp"
#include "shaka_scheme/system/lexer/rules/rule_character.hpp"

namespace shaka {
namespace lexer {
namespace rules {

LexerRule dot = make_terminal(".", "dot");
LexerRule comma_atsign = make_terminal(",@", "comma-atsign");
LexerRule comma = make_terminal(",", "comma");
LexerRule backtick = make_terminal("`", "backtick");
LexerRule quote = make_terminal("'", "quote");
LexerRule bytevector_left = make_terminal("#u8(", "bytevector-left");
LexerRule vector_left = make_terminal("#(", "vector-left");
LexerRule paren_right = make_terminal(")", "paren-right");
LexerRule paren_left = make_terminal("(", "paren-left");

LexerRule token = identifier
    | boolean
    //| number
    | character
    | string_rule
    | paren_left
    | paren_right
    | vector_left
    | bytevector_left
    | quote
    | backtick
    | comma_atsign
    | comma
    | dot;

} // namespace rules
} // namespace lexer
} // namespace shaka

#endif //SHAKA_SCHEME_RULE_TOKEN_HPP
