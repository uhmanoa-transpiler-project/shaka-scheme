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
  NodePtr vars = list(create_node(x_data), create_node(y_data));
  NodePtr body = list(create_node(plus), create_node(x_data),
                      create_node(y_data));
  Expression e = list(create_node(lambda), vars, body);

  // When: You compile the expression.
  Expression expression = compiler.compile(e);


  std::stringstream ss;
  ss << *expression;
  std::string output = ss.str();

  // Then: The resulting assembly instruction should have the following form.
  std::stringstream ss_test;
  ss_test << "(close (x y) (frame (halt) (refer y (argument (refer x (argument";
  ss_test << " (refer + (apply))))))) (halt))";
  ASSERT_EQ(output, ss_test.str());

  // Given: The expression (lambda (k) (k 'a) 'b)
  Data k_data(Symbol("k"));
  Data a_data(Symbol("a"));
  Data b_data(Symbol("b"));

  vars = list(create_node(k_data));
  NodePtr k_a = list(create_node(k_data), create_node(a_data));
  body = list(k_a, create_node(b_data));

  e = cons(create_node(lambda), cons(vars, body));
  // When: You compile the expression.
  Expression expression_two = compiler.compile(e);

  std::stringstream ss2;
  ss2 << *expression_two;
  output = ss2.str();

  // Then: The resulting assembly instruction should have the following form.
  std::stringstream ss_test_two;
  ss_test_two << "(close (k) (frame (refer b (halt)) (refer a (argument ";
  ss_test_two << "(refer k (apply))))) (halt))";
  ASSERT_EQ(output, ss_test_two.str());

  // Given: The expression (lambda (a b c) a b c)
  Data c_data(Symbol("c"));

  vars = list(create_node(a_data), create_node(b_data), create_node(c_data));
  e = list(create_node(lambda), vars, create_node(a_data), create_node(b_data),
           create_node(c_data));

  // When: You compile the expression.
  Expression expression_three = compiler.compile(e);

  std::stringstream ss3;
  ss3 << *expression_three;
  output = ss3.str();

  // Then: The resulting assembly instruction should have the following form.
  std::stringstream ss_test_three;
  ss_test_three <<"(close (a b c) (refer a (refer b (refer c (halt)))) (halt))";
  ASSERT_EQ(output, ss_test_three.str());

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

  Expression then_expression = list(create_node(plus), create_node(x_data),
                                    create_node(y_data));

  Expression else_expression = list(create_node(minus), create_node(x_data),
                                    create_node(y_data));

  // Given: The expression (if x (+ x y) (- x y))
  Expression e = list(create_node(if_op), create_node(x_data), then_expression,
                      else_expression);

  // When: You compile the expression.
  Expression expression = compiler.compile(e);

  std::stringstream ss;
  ss << *expression;
  std::string output = ss.str();


  // Then: The resulting assembly instruction will have the following form.
  std::stringstream ss_test;
  ss_test << "(refer x (test (frame (halt) (refer y (argument (refer x ";
  ss_test <<"(argument (refer + (apply))))))) (frame (halt) (refer y (argument";
  ss_test << " (refer x (argument (refer - (apply)))))))))";
  ASSERT_EQ(output, ss_test.str());
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


  // Then: The resulting assembly instruction will have the following form.
  std::stringstream ss;
  ss << *expression;
  std::string output = ss.str();
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

  // Then: The resulting assembly instruction should have the following form.
  std::stringstream ss;
  ss << *expression;
  std::string output = ss.str();
  ASSERT_EQ(output, "(frame (halt) (refer y (argument (refer x (argument "
      "(refer + (apply)))))))");
}

/**
 * @brief Test: compile() changing constants to 'constant' instructions
 */
TEST(CompilerUnitTest, constant_test) {
  Compiler compiler;
  Data hello(String("hello"));

  // Given: The expression "hello"
  Expression e = create_node(hello);

  // When: You compile the expression.
  Expression compiled_expression = compiler.compile(e);

  // Then: The resulting assembly instruction should have the following form.
  std::stringstream ss;
  ss << *compiled_expression;
  std::string output = ss.str();
  ASSERT_EQ(output, "(constant \"hello\" (halt))");
}

/**
 * @brief Test: If an expression is a tail call.
 */
//TEST(CompilerUnitTest, is_tail_test) {
//  ASSERT_TRUE(false);
//}


