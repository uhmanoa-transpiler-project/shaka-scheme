#include <gmock/gmock.h>

#include "shaka_scheme/system/parser/parser_definitions.hpp"


using namespace shaka;
/**
 * @brief Test: mock define expression
 */
TEST(ParserUnitTest, define) {
  // Given: an input string
  std::string buf = "(define a \"hello world\")";

  // Given: a ParserInput loaded with the input string.
  parser::ParserInput input(buf);

  // Given: the results will end up in this results vector.
  auto result = parser::parse_datum(input);
  std::cout << result << std::endl;
}

/**
 * @brief Test: mock define expression
 */
TEST(ParserUnitTest, set) {
  // Given: an input string
  std::string buf = "(set! |low vara| \"hello world\")";

  // Given: a ParserInput loaded with the input string.
  parser::ParserInput input(buf);

  // Given: the results will end up in this results vector.
  auto result = parser::parse_datum(input);
  std::cout << result << std::endl;
}
