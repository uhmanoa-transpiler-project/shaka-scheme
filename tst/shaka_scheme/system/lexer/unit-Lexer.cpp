#include <gmock/gmock.h>

#include "shaka_scheme/system/lexer/lexer_definitions.hpp"


using namespace shaka::lexer;
/**
 * @brief Test: Matching parentheses for ParerRules
 */
TEST(LexerUnitTest, matching_parens_success) {

  // Given: an input with matching parentheses
  std::string buf = "(()(()))";

  // Given: a LexerInput loaded with the input string.
  LexerInput lex(buf, "test");

  // Given: the results will end up in this results vector.
  std::vector<LexResult> results;

  //// Given: a procedure to print the current result after a parse
  //auto make_print = [](std::string str) {
  //  return [=](LexResult result) {
  //    std::cout << str << " : " << result << std::endl;
  //  };
  //};

  //// Given: a procedure to print a string before a parse
  //auto print_str = [](std::string str) {
  //  return [=](LexerInput& lex) {
  //    std::cout << str << std::endl;
  //  };
  //};

  // Given: left and right parenthesis terminal parsers
  auto lparen = make_terminal("(", "left-paren");
      // & make_print("    [left-paren]");
  auto rparen = make_terminal(")", "right-paren");
      // & make_print("    [right-paren]");

  // Given: composing left and right parenthesis terminal parsers is valid,
  // and renaming of parser tokens is possible with the operator/
  auto paren_pair = (lparen + rparen) / "paren-pair";

  // Given: a recursive and context-sensitive rule that consists of:
  // <nested_parens> ::= '(' , <nested_parens>* , ')'
  LexerRule nested_parens = [&](LexerInput& input) -> LexResult {
    return ((lparen + (*nested_parens) + rparen) / "nested_parens")(input);
  };

  // Given: a rule that can detect one or more nested parens
  LexerRule many_nested_parens = nested_parens + *nested_parens;

  // When: you parse a token using the many_nested_parens rule
  results.push_back(many_nested_parens(lex));

  // Then: the resulting token will have started at the position 1 mark
  LexInfo answer = {"test", 1, 1, 1};
  ASSERT_EQ(results[0].info, answer);

  // Then: the parser will be at the end of the string with the correct LexInfo
  LexInfo lex_lexinfo_answer = {"test", 9, 1, 9};
  ASSERT_EQ(lex.info, lex_lexinfo_answer);

  // Then: the LexResult will be a token of type "nested_parens+empty"
  ASSERT_EQ(results[0].type, "token");
  ASSERT_EQ(results[0].token_type, "nested_parens+empty");

  // Then: the LexResult will contain the original string.
  ASSERT_EQ(results[0].str, buf);
}

