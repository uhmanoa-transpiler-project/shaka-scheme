#include <gmock/gmock.h>

#include "shaka_scheme/system/lexer/rules/rule_comment.hpp"

using namespace shaka::lexer;
/**
 * @brief Test: line comments
 */
TEST(rule_comment_UnitTest, line_comment) {
  // Given: an input with a line comment
  std::string buf = "; hello my name is George ;;;\t\n";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");

  // When: you try to parse a line comment
  LexResult result = rules::line_comment(lex);

  // Then: we should get a line comment for the entire line
  ASSERT_EQ(result.str, buf);
  ASSERT_EQ(result.token_type, "line-comment");
}

/**
 * @brief Test: nested comments, one level deep
 */
TEST(rule_comment_UnitTest, nested_comment_one_level) {
  // Given: an input with a nested comment
  std::string buf = "#| the summer breeze high\nnights are belonging to\nthe "
      "daily struggle\n |#";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");

  // When: you try to parse a nested comment
  LexResult result = rules::nested_comment(lex);

  std::cout << result << std::endl;
  // Then: we should get a line comment for the entire line
  ASSERT_EQ(result.str, buf);
  ASSERT_EQ(result.token_type, "nested-comment");
}

/**
 * @brief Test: nested comments, three levels deep
 *
 * @note This appears to be broken. The rules need more tweaking.
 */
TEST(rule_comment_UnitTest, nested_comment_three_levels) {
  // Given: an input with a nested comment
  std::string buf = "#|a #|b #|hi my name is goat |# |# |#";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");

  // When: you try to parse a nested comment
  LexResult result = rules::nested_comment(lex);

  std::cout << result << std::endl;
  // Then: we should get a line comment for the entire line
  ASSERT_EQ(result.str, buf);
  ASSERT_EQ(result.token_type, "nested-comment");
}
