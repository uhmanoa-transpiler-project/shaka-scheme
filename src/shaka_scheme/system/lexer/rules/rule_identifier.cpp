#include "shaka_scheme/system/lexer/rules/rule_identifier.hpp"

namespace shaka {
namespace lexer {
namespace rules {

LexerRule special_initial;
LexerRule initial;
LexerRule explicit_sign;

LexerRule special_subsequent;

LexerRule subsequent;

LexerRule sign_subsequent;
LexerRule dot_subsequent;
LexerRule peculiar_identifier;

LexerRule symbol_element;

LexerRule identifier;

void init_rule_identifier() {
  special_initial = make_class([](char c) {
    return (c == '!') |
        (c == '$') |
        (c == '%') |
        (c == '&') |
        (c == '*') |
        (c == '/') |
        (c == '<') |
        (c == '=') |
        (c == '>') |
        (c == '?') |
        (c == '^') |
        (c == '_') |
        (c == '~');
  }, "special-initial");
  initial = (letter | special_initial) / "initial";
  explicit_sign = make_class([](char c) {
    return c == '+' || c == '-';
  }, "explicit-sign");

  special_subsequent = make_class([](char c) {
    return (c == '+') |
        (c == '-') |
        (c == '.') |
        (c == '@');
  }, "special-subsequent");

  subsequent = (initial | digit | special_subsequent) / "subsequent";

  sign_subsequent = (initial | explicit_sign | make_terminal("@"))
      / "sign-subsequent";
  dot_subsequent = (make_terminal(".") | sign_subsequent)
      / "dot-subsequent";
  peculiar_identifier =
      ((explicit_sign +
          ((sign_subsequent + *subsequent)
              | (make_terminal(".") + dot_subsequent + *subsequent)
              | (empty_string))) |
          ((make_terminal(".")) + dot_subsequent + *subsequent))
          / "peculiar-identifier";

  symbol_element = ((inline_hex_escape) |
      mnemonic_escape |
      make_terminal("\\|") | make_class([](char c) {
    return c != '|' && c != '\\';
  }, "not | or \\")) / "symbol-element";

  identifier =
      ((initial + *subsequent)
          | ((make_terminal("|") & ignore_string) + *symbol_element +
              (make_terminal("|")& ignore_string))
          | (peculiar_identifier)) / "identifier";
}

} // namespace rules
} // namespace lexer
} // namespace shaka
