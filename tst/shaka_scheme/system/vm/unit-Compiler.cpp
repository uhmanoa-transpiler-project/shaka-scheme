//
// Created by dylan on 10/6/17.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/vm/compiler/Compiler.hpp"

using namespace shaka;
using namespace core;

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

/**
 * @brief Test: compile() changing lambda expressions to 'close' instructions
 */
TEST(CompilerUnitTest, lambda_test) {
  Compiler compiler;
  Data x_data(Symbol("x"));
  Data y_data(Symbol("y"));
  Data plus(Symbol("+"));
  Data lambda(Symbol("lambda"));

  // Given: The expression (lambda (x y) (+ x y))
  Expression vars = list(create_node(x_data), create_node(y_data));
  Expression body = list(create_node(plus), create_node(x_data), create_node
      (y_data));
  Expression e = list(create_node(lambda), vars, body);

  // When: You compile the expression.
  Expression expression = compiler.compile(e);

  std::stringstream ss;
  ss << *expression;
  std::string output = ss.str();

  // Then: The resulting assembly instruction should have the following form.
  ASSERT_EQ(output, "(close (x y) (refer y (argument (refer x (argument "
      "(refer + (apply)))))) (halt))");


}

/**
 * @brief Test: compile() changing if expressions to 'test' instructions
 */
TEST(CompilerUnitTest, if_test) {
  Compiler compiler;
  Data x_data(Symbol("x"));
  Data y_data(Symbol("y"));
  Data if_op(Symbol("if"));
  Data minus(Symbol("-"));
  Data plus(Symbol("+"));


  Expression _then = list(create_node(plus), create_node(x_data), create_node
      (y_data));
  Expression _else = list(create_node(minus), create_node(x_data),
                          create_node(y_data));
  Expression e = list(create_node(if_op), _then, _else);

  Expression expression = compiler.compile(e);

  std::cout << *expression << std::endl;
  ASSERT_TRUE(false);
}

/**
 * @brief Test: compile() changing set expressions to 'assign' instructions
 */
TEST(CompilerUnitTest, set_test) {
  Compiler compiler;
  NodePtr set_bang = create_node(Data(Symbol("set!")));
  Data x_data(Symbol("x"));
  Data hello_string(String("hello"));

  // Given: The expression (set! x "hello")
  Expression e = list(set_bang, create_node(x_data), create_node(hello_string));

  // When: You compile the expression.
  Expression expression = compiler.compile(e);

  std::stringstream ss;
  ss << *expression;
  std::string output = ss.str();

  // Then: The resulting assembly instruction will have the following form.
  ASSERT_EQ(output, "(constant \"hello\" (assign x (halt)))");
}

/**
 * @brief Test: compile() changing call/cc expressions to 'frame' instructions
 */
TEST(CompilerUnitTest, call_cc_test) {

  ASSERT_TRUE(false);

}

/**
 * @brief Test: compile() changing applications to 'frame' instructions
 */
TEST(CompilerUnitTest, application_test) {
  Compiler compiler;
  Data x_data(Symbol("x"));
  Data y_data(Symbol("y"));
  Data plus(Symbol("+"));

  // Given: The expression (+ x y)
  Expression e = list(create_node(plus), create_node(x_data), create_node
      (y_data));

  // When: You compile the expression.
  Expression expression = compiler.compile(e);
  std::stringstream ss;
  ss << *expression;
  std::string output = ss.str();

  // Then: The resulting assembly instruction should have the following form.
  ASSERT_EQ(output, "(frame (halt) (refer y (argument (refer x (argument "
      "(refer + (apply)))))))");
}

/**
 * @brief Test: compile() changing constants to 'constant' instructions
 */
TEST(CompilerUnitTest, constant_test) {
 ASSERT_TRUE(false);
}

/**
 * @brief Test: If an expression is a tail call.
 */
TEST(CompilerUnitTest, is_tail_test) {
  ASSERT_TRUE(false);
}


