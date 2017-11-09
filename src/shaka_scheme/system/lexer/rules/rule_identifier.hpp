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

LexerRule special_initial = make_class([](char c) {
  return c == '!' |
      c == '$' |
      c == '%' |
      c == '&' |
      c == '*' |
      c == '/' |
      c == '<' |
      c == '=' |
      c == '>' |
      c == '?' |
      c == '^' |
      c == '_' |
      c == '~';
}, "special-initial");
LexerRule initial = (letter | special_initial) / "initial";
LexerRule explicit_sign = make_class([](char c) {
  return c == '+' || c == '-';
}, "explicit-sign");

LexerRule special_subsequent = make_class([](char c) {
  return c == '+' |
      c == '-' |
      c == '.' |
      c == '@';
}, "special-subsequent");

LexerRule subsequent = (initial | digit | special_subsequent) / "subsequent";

LexerRule sign_subsequent = (initial | explicit_sign | make_terminal("@"))
    / "sign-subsequent";
LexerRule dot_subsequent = (make_terminal(".") | sign_subsequent)
    / "dot-subsequent";
LexerRule peculiar_identifier =
    ((explicit_sign +
        ((sign_subsequent + *subsequent)
            | (make_terminal(".") + dot_subsequent + *subsequent)
            | (empty_string))) |
        ((make_terminal(".")) + dot_subsequent + *subsequent))
        / "peculiar-identifier";

LexerRule symbol_element = ((inline_hex_escape) |
    mnemonic_escape |
    make_terminal("\\|") | make_class([](char c) {
  return c != '|' && c != '\\';
}, "not | or \\")) / "symbol-element";

LexerRule identifier =
    ((initial + *subsequent)
        | ((make_terminal("|") & ignore_string) + *symbol_element +
            (make_terminal("|")& ignore_string))
        | (peculiar_identifier)) / "identifier";

} // namespace rules
} // namespace lexer
} // namespace shaka

#endif //SHAKA_SCHEME_RULE_IDENTIFIER_HPP
