#include "shaka_scheme/system/lexer/rules/rule_string.hpp"

namespace shaka {
namespace lexer {
namespace rules {

LexerRule double_quote = make_terminal("\"", "double-quote") & ignore_string;

LexerRule string_element =
    (mnemonic_escape
        | inline_hex_escape
        | (make_terminal("\\", "backslash") +
            *intraline_whitespace +
            line_ending + *intraline_whitespace)
        | (make_terminal("\\\"", "escaped-double-quote"))
        | (make_terminal("\\\\", "escaped-backslash"))
        | (make_class([](char c) {
          return c != '\"' && c != '\\';
          //return std::isalpha(c);
        }, "not \" or \\")));

LexerRule string_rule = (double_quote + *string_element + double_quote) /
    "string";

} // namespace rules
} // namespace lexer
} // namespace shaka
