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
#include "shaka_scheme/system/lexer/rules/rule_number.hpp"
#include "shaka_scheme/system/lexer/rules/rule_comment.hpp"

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
LexerRule datum_comment = make_terminal("#;", "datum-comment");

LexerRule directive = ((make_terminal("#!") & ignore_string) + identifier) /
    "directive";

LexerRule token = identifier
    | boolean
    | number
    | character
    | string_rule
    | directive
    | paren_left
    | paren_right
    | vector_left
    | bytevector_left
    | datum_comment
    | quote
    | backtick
    | comma_atsign
    | comma
    | dot;

LexerRule atmosphere = (make_class([](char c) {
  return std::isspace(c);
}, "whitespace") | comment);

LexerRule intertoken_space = *atmosphere;

LexerRule scheme_lexer = [](LexerInput& lex) {
  intertoken_space(lex);
  auto result = token(lex);
  intertoken_space(lex);
  return result;
};



} // namespace rules
} // namespace lexer
} // namespace shaka

#endif //SHAKA_SCHEME_RULE_TOKEN_HPP
