#include <gmock/gmock.h>

#include "shaka_scheme/system/lexer/rules/rule_boolean.hpp"

using namespace shaka::lexer;

/**
 * @brief Test: true and false
 */
TEST(rule_identifier_UnitTest, boolean) {
  // Given: an input with a hexidecimal number
  std::string buf = "#t #f #true #false";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");

  std::vector<LexResult> results;

  auto skip_ws = *make_class([](char c) {
    return std::isspace(c);
  }, "whitespace");

  // When: you try to parse a series of booleans
  skip_ws(lex);
  LexResult result = rules::boolean(lex);
  while (result.is_token()) {
    results.push_back(result);
    skip_ws(lex);
    result = rules::boolean(lex);
  }
  for (auto it : results) {
    std::cout << it << std::endl;
  }
}

