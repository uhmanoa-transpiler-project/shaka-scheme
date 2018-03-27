#include <gmock/gmock.h>

#include "shaka_scheme/system/lexer/rules/init.hpp"
#include "shaka_scheme/system/parser/parser_definitions.hpp"
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"

using namespace shaka;
/**
 * @brief Test: mock define expression
 *
 * @todo Strengthen this unit test since it doesn't check the structure of the
 * parsed result
 */
TEST(ParserUnitTest, define) {
  gc::GC garbage_collector;
  gc::init_create_node(garbage_collector);
  // Given: the lexer rules are initialized
  lexer::rules::init_lexer_rules();

  // Given: an input string
  std::string buf = "(define a \"hello world\")";

  // Given: a ParserInput loaded with the input string
  parser::ParserInput input(buf);

  // When: the string is parsed
  auto result = parser::parse_datum(input);

  // Then: the results should be printable
  std::cout << result << std::endl;
}

/**
 * @brief Test: mock set expression
 */
TEST(ParserUnitTest, set) {
  gc::GC garbage_collector;
  gc::init_create_node(garbage_collector);
  // Given: the lexer rules are initialized
  lexer::rules::init_lexer_rules();

  // Given: an input string
  std::string buf = "(set! |low vara| \"hello world\")";

  // Given: a ParserInput loaded with the input string
  parser::ParserInput input(buf);

  // When: the input string is parsed
  auto result = parser::parse_datum(input);

  // Then: the results can be printed out
  std::cout << result << std::endl;
}

/**
 * @brief Test: parse vector expression
 */
TEST(ParserUnitTest, vector) {
  // Given: the lexer rules are initialized
  lexer::rules::init_lexer_rules();

  // Given: an input string with a 3-element vector
  std::string buf = "#(1 \"hello world\" 'set)";

  // Given: a ParserInput loaded with the input string
  parser::ParserInput input(buf);

  // When: the input string is parsed
  auto result = parser::parse_datum(input);

  // Then: the parser result can be unpacked and a shaka::Vector can be
  // obtained from it
  Vector v = result.it->get<shaka::Vector>();

  // Then: the vector will be of size 3
  ASSERT_EQ(v.length(), 3);

  // Then: the first element will be 1
  ASSERT_EQ(v[0]->get<shaka::Number>(), shaka::Number(1));

  // Then: the second element will be "hello world"
  ASSERT_EQ(v[1]->get<shaka::String>(), shaka::String("hello world"));

  // Then: the third element will be a list of form (quote set)
  auto third_element = v[2]->get<shaka::DataPair>();
  ASSERT_EQ(third_element.car()
                ->get<shaka::Symbol>(),
            shaka::Symbol("quote"));
  ASSERT_EQ(third_element.cdr()
                ->get<shaka::DataPair>()
                .car()->get<shaka::Symbol>(),
            shaka::Symbol("set"));
  ASSERT_EQ(third_element.cdr()
                ->get<shaka::DataPair>()
                .cdr()->get_type(),
            shaka::Data::Type::NULL_LIST);
}

/**
 * @brief Test: parse valid bytevector expression
 *
 * @todo Strengthen this unit test since it doesn't check the structure of the
 * parsed result
 */
TEST(ParserUnitTest, bytevector_success) {
  // Given: the lexer rules are initialized
  lexer::rules::init_lexer_rules();

  // Given: an input string with a 3-element vector
  std::string buf = "#u8(0 123 255)";

  // Given: a ParserInput loaded with the input string
  parser::ParserInput input(buf);

  // When: the input string is parsed
  auto result = parser::parse_datum(input);

  // Then: the parser result can be unpacked and a shaka::Bytevector can be
  // obtained from it
  Bytevector bv = result.it->get<shaka::Bytevector>();
}

/**
 * @brief Test: parse invalid bytevector expression with negative integer
 */
TEST(ParserUnitTest, bytevector_negative_integer_element_failure) {
  // Given: the lexer rules are initialized
  lexer::rules::init_lexer_rules();

  // Given: an invalid bytevector string with a negative integer
  std::string buf = "#u8(-1)";

  // Given: a ParserInput loaded with the input string
  parser::ParserInput input(buf);

  // When: the input string is parsed
  auto result = parser::parse_datum(input);

  // Then: the parser input should be invalid with a ParserError
  ASSERT_TRUE(result.is_parser_error());
}

/**
 * @brief Test: parse invalid bytevector expression with non-Number elements
 */
TEST(ParserUnitTest, bytevector_non_number_element_failure) {
  // Given: the lexer rules are initialized
  lexer::rules::init_lexer_rules();

  // Given: an invalid bytevector string with a Symbol and String
  std::string buf = "#u8('set \"hi\")";

  // Given: a ParserInput loaded with the input string
  parser::ParserInput input(buf);

  // When: the input string is parsed
  auto result = parser::parse_datum(input);

  // Then: the parser input should be invalid with a ParserError
  ASSERT_TRUE(result.is_parser_error());
}


