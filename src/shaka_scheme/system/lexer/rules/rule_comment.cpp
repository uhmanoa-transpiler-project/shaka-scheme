#include "shaka_scheme/system/lexer/rules/rule_comment.hpp"

namespace shaka {
namespace lexer {
namespace rules {

// line comment
LexerRule line_comment;

// nested comment
LexerRule nested_comment_left;
LexerRule nested_comment_right;
LexerRule nested_comment_delimiter;
LexerRule comment_text;

LexerRule nested_comment;

LexerRule comment;

void init_rule_comment() {
// line comment
  line_comment = (semicolon + *not_newline + newline) / "line-comment";
// nested comment
  nested_comment_left = make_terminal("#|", "nested-comment-left");
  nested_comment_right = make_terminal("|#", "nested-comment-right");
  nested_comment_delimiter = nested_comment_left | nested_comment_right;
  comment_text = (!nested_comment_delimiter
      + make_class([](char c) { return true; }, "non-nested-comment-delimiter"))
      / "comment-text";
  nested_comment = [](LexerInput& input) {
    LexerRule recurse;
    recurse = [&](LexerInput& input) {
      LexerRule comment_cont = (recurse + comment_text);
      return ((nested_comment_left + *comment_text +
          *comment_cont +
          nested_comment_right) / "nested-comment")(input);
    };
    return recurse(input);
  };
  comment = line_comment | nested_comment;
}

} // namespace rules
} // namespace lexer
} // namespace shaka


