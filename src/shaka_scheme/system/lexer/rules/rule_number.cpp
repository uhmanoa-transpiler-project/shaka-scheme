#include "shaka_scheme/system/lexer/rules/rule_comment.hpp"

namespace shaka {
namespace lexer {
namespace rules {

LexerRule sign;
LexerRule whole_number;
LexerRule integer;
LexerRule real;
LexerRule rational;
LexerRule number;

void init_rule_number() {
  sign = (make_terminal("+") | make_terminal("-")) / "sign";
  whole_number = (digit + *digit) / "whole_number";
  integer   = ((sign|empty_string) + whole_number) / "integer";
  real      = (integer + make_terminal(".") +
      whole_number) / "real";
  rational  = (integer + make_terminal("/") + integer) / "rational";
  number = rational | real | integer;
}

} // namespace rules
} // namespace lexer
} // namespace shaka
