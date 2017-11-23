//
// Created by aytas on 11/1/2017.
//

#ifndef SHAKA_SCHEME_COMMON_RULES_HPP
#define SHAKA_SCHEME_COMMON_RULES_HPP

#include "shaka_scheme/system/lexer/lexer_definitions.hpp"

#include <cctype>

namespace shaka {
namespace lexer {
namespace rules {

extern LexerRule letter;
extern LexerRule digit;
extern LexerRule hex_digit;
extern LexerRule hex_scalar_value;

extern std::function<LexResult(LexResult)> ignore_string;

extern std::function<LexResult(LexResult)> print_string;

extern std::function<LexResult(LexResult)> print_result;

void print_lexstate(LexerInput& input);

std::function<LexResult(LexResult)> print_message(std::string message);

std::function<void(LexerInput&)> prefix_message(std::string message);

std::function<LexResult(LexResult)> replace_with(const std::string s);

LexResult replace_hex_escape(LexResult result);

LexResult replace_hex_scalar_value(LexResult result);

LexResult replace_mnemonic_escape(LexResult result);

extern LexerRule inline_hex_escape;

extern LexerRule mnemonic_escape;

extern LexerRule intraline_whitespace;

extern LexerRule carriage_return;
extern LexerRule not_newline;
extern LexerRule semicolon;
extern LexerRule newline;

extern LexerRule line_ending;

} // namespace rules
} // namespace lexer
} // namespace shaka

#endif //SHAKA_SCHEME_COMMON_RULES_HPP
