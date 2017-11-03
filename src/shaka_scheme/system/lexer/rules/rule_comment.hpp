//
// Created by aytas on 10/31/2017.
//

#ifndef SHAKA_SCHEME_RULE_COMMENT_HPP
#define SHAKA_SCHEME_RULE_COMMENT_HPP

#include "shaka_scheme/system/lexer/lexer_definitions.hpp"

namespace shaka {
namespace lexer {
namespace rules {

// line comment
LexerRule line_comment = (semicolon + *not_newline + newline) / "line-comment";

// nested comment
LexerRule nested_comment_left = make_terminal("#|", "nested-comment-left");
LexerRule nested_comment_right = make_terminal("|#", "nested-comment-right");
LexerRule nested_comment_delimiter = nested_comment_left | nested_comment_right;
LexerRule comment_text = (!nested_comment_delimiter + make_class([](char c) { return true; }, "non-nested-comment-delimiter")) / "comment-text";

LexerRule nested_comment = [&](LexerInput& input) {
    LexerRule comment_cont = (nested_comment + comment_text);
    return ((nested_comment_left + *comment_text +
        *comment_cont +
        nested_comment_right) / "nested-comment")(input);
};

LexerRule comment = line_comment | nested_comment;

} // namespace rules
} // namespace lexer
} // namespace shaka

#endif //SHAKA_SCHEME_RULE_COMMENT_HPP
