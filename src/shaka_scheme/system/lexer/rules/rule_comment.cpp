#include "shaka_scheme/system/lexer/rules/rule_comment.hpp"

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

LexerRule nested_comment = [](LexerInput& input) {
  LexerRule recurse;
  recurse = [&](LexerInput& input) {
    LexerRule comment_cont = (recurse + comment_text);
    return ((nested_comment_left + *comment_text +
        *comment_cont +
        nested_comment_right) / "nested-comment")(input);
  };
  return recurse(input);
};

LexerRule comment = line_comment | nested_comment;

} // namespace rules
} // namespace lexer
} // namespace shaka


