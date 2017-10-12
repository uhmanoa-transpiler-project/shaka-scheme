//
// Created by Billy Wooton on 10/11/17.
//

#include <gmock/gmock.h>
#include <iostream>
#include "shaka_scheme/system/vm/Closure.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/base/Environment.hpp"
#include "shaka_scheme/system/core/lists.hpp"
#include "shaka_scheme/system/vm/strings.hpp"

using namespace shaka;


/**
 * @brief Test: Constructor usage for constructing generic closure
 */
TEST(ClosureUnitTest, constructor) {

  // Given: A pointer to an environment with no bindings

  EnvPtr env(nullptr);

  // Given: A variable list with one symbol 'x

  std::vector<Symbol> vars = {Symbol("x")};

  // Given: A function body expression that is '(refer x (return))

  Symbol refer("refer");
  Symbol ret("return");
  Symbol x("x");
  Data ret_data(ret);
  Data x_data(x);
  Data refer_data(refer);
  DataPair ret_pair(ret_data);
  DataPair x_ret_pair(x_data,
                      *core::list(create_node(ret_pair)));
  DataPair refer_x_ret(refer_data, x_ret_pair);

  NodePtr body_expression = create_node(refer_x_ret);

  // Given: A null pointer to a Callable

  CallablePtr callable = nullptr;

  // Given: A null CallFrame pointer

  FramePtr call_frame = nullptr;

  // When: You construct a closure object with these items
  Closure identity(env, body_expression, vars, callable, call_frame);

  // Then: The body of the Closure will be (refer x (return))

  ASSERT_EQ(
      identity.get_function_body()->get<DataPair>().car()->get<Symbol>(),
      Symbol("refer")
  );

}

/**
 * @brief Test: Usage of extend_environment method
 */
TEST(ClosureUnitTest, extend_environment) {

  // Given: A pointer to an environment with no bindings

  EnvPtr env = std::make_shared<Environment>(nullptr);

  // Given: A variable list with one symbol 'x

  std::vector<Symbol> vars = {Symbol("x")};

  // Given: A function body expression that is '(refer x (return))

  Symbol refer("refer");
  Symbol ret("return");
  Symbol x("x");
  Data ret_data(ret);
  Data x_data(x);
  Data refer_data(refer);
  DataPair ret_pair(ret_data);
  DataPair x_ret_pair(x_data,
                      *core::list(create_node(ret_pair)));
  DataPair refer_x_ret(refer_data, x_ret_pair);

  NodePtr body_expression = create_node(refer_x_ret);

  // Given: A null pointer to a Callable

  CallablePtr callable = nullptr;

  // Given: A null CallFrame pointer

  FramePtr call_frame = nullptr;

  // Given: A ValueRib with the string "Hello"

  ValueRib vr = {create_node(String("Hello"))};

  // Given: You construct a closure object with these items
  Closure identity(env, body_expression, vars, callable, call_frame);

  // When: You extend the closure objects environment with the value rib
  identity.extend_environment(vr);

  // Then: The closure's environment will have binding [x : "Hello"]

  ASSERT_EQ(
      identity.get_environment()->get_value(Symbol("x")),
      vr[0]
  );
}

/**
 * @brief Test: Using the call method for a NativeClosure string-length
 */
TEST(ClosureUnitTest, call) {

}

