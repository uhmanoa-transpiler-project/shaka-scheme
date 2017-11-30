#include <gmock/gmock.h>

#include "shaka_scheme/system/lexer/rules/rule_string.hpp"

using namespace shaka::lexer;

/**
 * @brief Test: string
 */
TEST(rule_string_UnitTest, string) {
  // Given: the lexer rules are initialized
  rules::init_common_rules();
  rules::init_rule_string();
  
  // Given: an input with a hexidecimal number
  std::string buf = "\"two\\x20;words\"";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");

  // When: you try to parse a string
  LexResult result = rules::string_rule(lex);
  std::cout << result << std::endl;
  ASSERT_EQ(result.str, "two words");
}

