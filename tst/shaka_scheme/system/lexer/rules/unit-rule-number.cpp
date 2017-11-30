#include <gmock/gmock.h>

#include "shaka_scheme/system/lexer/rules/rule_number.hpp"

using namespace shaka::lexer;

/**
 * @brief Test: hex digits
 */
TEST(rule_number_UnitTest, number) {
  // Given: the lexer rules are initialized
  rules::init_common_rules();
  rules::init_rule_number();

  // Given: input with integer, real, and rational
  std::string buf = "123456 -123.123 +123/-123";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");


  auto skip_ws = *make_class([](char c) {
    return std::isspace(c);
  }, "whitespace");

  // When: you try to parse a Kleene star hex digit
  std::vector<LexResult> results;
  LexResult result = rules::number(lex);
  while (result.is_token()) {
    //std::cout << result << std::endl;
    results.push_back(result);
    skip_ws(lex);
    result = rules::number(lex);
  }

  ASSERT_EQ(results[0].str, "123456");
  ASSERT_EQ(results[1].str, "-123.123");
  ASSERT_EQ(results[2].str, "+123/-123");


  // Then: we should get a hex number for the entire line

}

