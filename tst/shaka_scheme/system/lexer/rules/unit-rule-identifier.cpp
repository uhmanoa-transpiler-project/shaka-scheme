#include <gmock/gmock.h>

#include "shaka_scheme/system/lexer/rules/rule_identifier.hpp"

using namespace shaka::lexer;

/**
 * @brief Test: hex digits
 */
TEST(rule_identifier_UnitTest, hex_digits) {
  // Given: an input with a hexidecimal number
  std::string buf = "0123456789adcf";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");

  // When: you try to parse a Kleene star hex digit
  LexResult result = (*rules::hex_digit)(lex);

  // Then: we should get a hex number for the entire line
  ASSERT_EQ(result.str, buf);
  ASSERT_EQ(result.token_type, "*hex-digit");
}

/**
 * @brief Test: inline hex escape
 */
TEST(rule_identifier_UnitTest, inline_hex_escape) {
  // Given: an input with a hexidecimal number
  std::string buf = "\\x20;";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");

  // When: you try to parse a Kleene star hex digit
  LexResult result = rules::inline_hex_escape(lex);

  // Then: we should get a hex number for the entire line
  ASSERT_EQ(result.str, " ");
  ASSERT_EQ(result.token_type, "inline-hex-escape");
}

/**
 * @brief Test: identifier
 */
TEST(rule_identifier_UnitTest, identifier) {
  // Given: an input with a hexidecimal number
  std::string buf = "... + +soup+ <=? ->string a34kTMNs lambda list->vector q"
      " V17a |two words| |two\\x20;words| the-word-recursion-has-many-meanings";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");

  std::vector<LexResult> results;

  auto skip_ws = *make_class([](char c) {
    return std::isspace(c);
  }, "whitespace");

  // When: you try to parse a series of identifier
  skip_ws(lex);
  LexResult result = rules::identifier(lex);
  while (!result.is_incomplete()) {
    results.push_back(result);
    skip_ws(lex);
    result = rules::identifier(lex);
  }

  for (auto it : results) {
    std::cout << it << std::endl;
  }

  // Then: we should get a hex number for the entire line
}
