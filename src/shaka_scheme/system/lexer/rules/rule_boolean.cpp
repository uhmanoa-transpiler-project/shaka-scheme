#include "shaka_scheme/system/lexer/rules/rule_boolean.hpp"

namespace shaka {
namespace lexer {
namespace rules {


LexerRule boolean_true;

LexerRule boolean_false;

LexerRule boolean;

void init_rule_boolean() {
  boolean_true = (make_terminal("#true") | make_terminal("#t"))
      /"boolean-true";

  boolean_false = (make_terminal("#false") | make_terminal("#f"))
      /"boolean-false";

  boolean = boolean_true | boolean_false;
}

} // namespace rules
} // namespace lexer
} // namespace shaka
