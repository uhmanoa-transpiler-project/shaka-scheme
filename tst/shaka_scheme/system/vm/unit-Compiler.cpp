//
// Created by dylan on 10/6/17.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/vm/compiler/Compiler.hpp"

using namespace shaka;

/**
 * @brief Test: compile() changing symbols to 'refer' instructions
 */
TEST(CompilerUnitTest, is_symbol_test) {
  // Given: A symbol "a"
  Symbol var("a");
  Data var_data(var);
  Compiler compiler;

  // When: You send the symbol to the compiler.
  Expression expression = compiler.compile(create_node(var_data));

  // Then: The resulting assembly instruction will match the following format.
  std::stringstream ss;
  ss << *expression;
  std::string output = ss.str();
  ASSERT_EQ(output, "(refer a (halt))");
}

/**
 * @brief Test: compile() changing quote expressions to 'constant' instructions
 */
TEST(CompilerUnitTest, quote_test) {
  // Given: The expression (quote "Hello")
  String obj("Hello");
  Symbol quote("quote");
  Data obj_data(obj);
  Data quote_data(quote);
  DataPair constant_obj_pair(quote_data, obj_data);
  Compiler compiler;

  // When: You send the expression to the compiler.
  Expression expression = compiler.compile(create_node(constant_obj_pair));

  // Then: The resulting assembly instruction will match the following format.
  std::stringstream ss;
  ss << *expression;
  std::string output = ss.str();
  ASSERT_EQ(output, "(constant \"Hello\" (halt))");
}
