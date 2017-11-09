//
// Created by aytas on 11/1/2017.
//

#ifndef SHAKA_SCHEME_RULE_NUMBER_HPP
#define SHAKA_SCHEME_RULE_NUMBER_HPP

#include "shaka_scheme/system/lexer/rules/common_rules.hpp"

#include <cctype>

namespace shaka {
namespace lexer {
namespace rules {

LexerRule sign = (make_terminal("+") | make_terminal("-")) / "sign";
LexerRule whole_number = (digit + *digit) / "whole_number";
LexerRule integer   = ((sign|empty_string) + whole_number) / "integer";
LexerRule real      = (integer + make_terminal(".") +
    whole_number) / "real";
LexerRule rational  = (integer + make_terminal("/") + integer) / "rational";

LexerRule number = rational | real | integer;

} // namespace rules
} // namespace lexer
} // namespace shaka


#endif //SHAKA_SCHEME_RULE_NUMBER_HPP
