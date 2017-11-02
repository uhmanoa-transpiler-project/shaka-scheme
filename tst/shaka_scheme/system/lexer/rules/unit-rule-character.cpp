#include <gmock/gmock.h>
#include <shaka_scheme/system/lexer/lexer_definitions.hpp>

#include "shaka_scheme/system/lexer/rules/rule_character.hpp"

using namespace shaka::lexer;

/**
 * @brief Test: character
 */
TEST(rule_character_UnitTest, character) {
  // Given: an input with a hexidecimal number
  std::string buf = "#\\x20 #\\; #\\tab";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");


  std::vector<LexResult> results;

  auto skip_ws = *make_class([](char c) {
    return std::isspace(c);
  }, "whitespace");

  // When: you try to parse a series of identifier
  skip_ws(lex);
  // When: you try to parse a string
  LexResult result = rules::character(lex);
  while (result.is_token()) {
    results.push_back(result);
    skip_ws(lex);
    result = rules::character(lex);
  }

  ASSERT_EQ(results[0].str, " ");
  ASSERT_EQ(results[1].str, ";");
  ASSERT_EQ(results[2].str, "\t");
}

