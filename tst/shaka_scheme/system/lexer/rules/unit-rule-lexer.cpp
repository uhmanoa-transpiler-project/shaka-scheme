#include <gmock/gmock.h>

#include "shaka_scheme/system/lexer/rules/common_rules.hpp"
#include "shaka_scheme/system/lexer/rules/rule_character.hpp"

using namespace shaka::lexer;

/**
 * @brief Test: true and false
 */
TEST(rule_identifier_UnitTest, boolean) {

  // Given: the lexer rules are initialized
  rules::init_common_rules();
  rules::init_rule_character();

  // Given: an input with a hexidecimal number
  std::string buf = "#\\x20 #\\; #\\tab";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");

  std::vector<LexResult> results;

  std::cout << (void*)(rules::character.target<LexResult (*) (LexerInput&)>() )
            << std::endl;

  auto skip_ws = *make_class([](char c) {
    return std::isspace(c);
  }, "whitespace");

  // When: you try to parse a series of booleans
  skip_ws(lex);
  LexResult result = rules::character(lex);
  while (result.is_token()) {
    results.push_back(result);
    skip_ws(lex);
    result = rules::character(lex);
  }
  for (auto it : results) {
    std::cout << it << std::endl;
  }
}

