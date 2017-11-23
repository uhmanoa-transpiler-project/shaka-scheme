#include "shaka_scheme/system/lexer/rules/rule_token.hpp"

namespace shaka {
namespace lexer {
namespace rules {

LexerRule dot;
LexerRule comma_atsign;
LexerRule comma;
LexerRule backtick;
LexerRule quote;
LexerRule bytevector_left;
LexerRule vector_left;
LexerRule paren_right;
LexerRule paren_left;
LexerRule datum_comment;
LexerRule directive;
LexerRule token;

LexerRule atmosphere;
LexerRule intertoken_space;

LexerRule scheme_lexer;

void init_rule_token() {

  dot = make_terminal(".", "dot");
  comma_atsign = make_terminal(",@", "comma-atsign");
  comma = make_terminal(",", "comma");
  backtick = make_terminal("`", "backtick");
  quote = make_terminal("'", "quote");
  bytevector_left = make_terminal("#u8(", "bytevector-left");
  vector_left = make_terminal("#(", "vector-left");
  paren_right = make_terminal(")", "paren-right");
  paren_left = make_terminal("(", "paren-left");
  datum_comment = make_terminal("#;", "datum-comment");

  directive = ((make_terminal("#!") & ignore_string) + identifier) /
      "directive";

  token = identifier
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

  atmosphere = (make_class([](char c) {
    return std::isspace(c);
  }, "whitespace") | comment);

  intertoken_space = *atmosphere;

  scheme_lexer = [](LexerInput& lex) {
    intertoken_space(lex);
    auto result = token(lex);
    return result;
  };
}

} // namespace rules
} // namespace lexer
} // namespace shaka
