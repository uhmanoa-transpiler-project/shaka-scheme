#include <gmock/gmock.h>

#include "shaka_scheme/system/lexer/rules/init.hpp"
#include "shaka_scheme/system/lexer/rules/rule_token.hpp"

using namespace shaka::lexer;
/**
 * @brief Test: token rule
 */
TEST(rule_token_UnitTest, token_literals) {
  // Given: the lexer rules are initialized
  rules::init_lexer_rules();

  // Given: an input with various tokens
  std::string buf = "( ) #( #u8( , . ` ,@";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");

  // Given: the results will end up in this results vector.
  std::vector<LexResult> results;


  auto space = make_class([](char c) { return std::isspace(c); },
                            "whitespace");

  auto skip_whitespace = *space;

  skip_whitespace(lex);
  LexResult result = rules::token(lex);
  while (result.is_token()) {
    results.push_back(result);
    skip_whitespace(lex);
    result = rules::token(lex);
  }

  for (auto it : results) {
    std::cout << it << std::endl;
  }

}

