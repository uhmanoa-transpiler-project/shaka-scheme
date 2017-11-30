//
// Created by Billy Wooton on 10/11/17.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/vm/Closure.hpp"
#include "shaka_scheme/system/vm/CallFrame.hpp"
#include "shaka_scheme/system/core/lists.hpp"
#include "shaka_scheme/system/core/strings.hpp"

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
  Closure identity(env, body_expression, vars, callable, call_frame, false);

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

  // Given: A closure object constructed with these items
  Closure identity(env, body_expression, vars, callable, call_frame, false);

  // When: You extend the closure objects environment with the value rib
  identity.extend_environment(vr);

  // Then: The closure's environment will have binding [x : "Hello"]

  ASSERT_EQ(
      identity.get_environment()->get_value(Symbol("x")),
      vr[0]
  );
}

/**
 * @brief Test: Using the call method for a NativeClosure string-append
 */
TEST(ClosureUnitTest, native_closure) {

  // Given: A pointer to an environment with no bindings

  EnvPtr env = std::make_shared<Environment>(nullptr);

  // Given: An empty variable list

  std::vector<Symbol> vars;

  // Given: A function body expression that is '(return)

  Symbol ret("return");
  Data ret_data(ret);
  DataPair ret_pair(ret_data);
  NodePtr body_expression = create_node(ret_pair);

  // Given: A pointer to the Callable for string-append

  CallablePtr string_append_ptr = std::make_shared<Callable>(string_append);

  // Given: A null CallFrame pointer

  FramePtr call_frame = nullptr;

  // Given: A ValueRib with the strings "Hello", "World", "Leaders"

  ValueRib vr = {
      create_node(String("Hello")),
      create_node(String("World")),
      create_node(String("Leaders"))
  };

  // Given: A Closure object constructed with these items

  Closure string_append_closure(env, body_expression,
                                vars, string_append_ptr, call_frame, true);

  // When: You call the closure on the items in the ValueRib

  ValueRib result = string_append_closure.call(vr);

  // Then: The string "HelloWorldLeaders" will be in the result vector

  ASSERT_EQ(result[0]->get<String>(), String("HelloWorldLeaders"));

  // Then: The closure should be correctly identifiable as native

  ASSERT_TRUE(string_append_closure.is_native_closure());
}

/**
 * @brief Test: Creation of a Continuation closure
 */
TEST(ClosureUnitTest, continuation_closure) {

  // Given: A pointer to an environment with no bindings

  EnvPtr env = std::make_shared<Environment>(nullptr);

  // Given: A variable list with the dummy variable symbol 'kont_v_000

  std::vector<Symbol> vars = {Symbol("kont_v_000")};

  // Given: A pointer to a CallFrame object

  ValueRib vr;

  FramePtr frame = std::make_shared<CallFrame>(
      core::list(create_node(Symbol("return"))),
      std::make_shared<Environment>(nullptr),
      vr,
      nullptr
  );

  // Given: The standard function body for a Continuation '(nuate s var)

  NodePtr func_body = core::list(
      create_node(Symbol("nuate")),
      create_node((*frame)),
      create_node(Symbol("kont_v_000"))
  );

  // When: You construct a continuation Closure with these items

  Closure continuation(env, func_body, vars, nullptr, frame, false);

  // Then: The continuation Closure should be correctly identifiable as such

  ASSERT_TRUE(continuation.is_continuation_closure());

  // Then: The function body of the Closure should be '(nuate s kont_v_000)

  ASSERT_EQ(
      continuation.get_function_body()->get<DataPair>().car()->get<Symbol>(),
      Symbol("nuate")
  );

  // Then: The Closure object should have a variable list containing kont_v_000

  ASSERT_EQ(continuation.get_variable_list()[0], Symbol("kont_v_000"));

  // Then: The Closure object should have a FramePtr that holds '(return)

  ASSERT_EQ(
      continuation.get_call_frame()->
              get_next_expression()->
              get<DataPair>().car()->get<Symbol>(), Symbol("return")
  );
}

/**
 * @brief Test: Closure functionality with a variadic lambda
 */
TEST(ClosureUnitTest, variadic_lambda) {

  // Simulation of the behavior of a procedure such as (lambda x x)

  // Given: A pointer to an environment with no bindings

  EnvPtr env = std::make_shared<Environment>(nullptr);

  // Given: A variable list that just holds the variable 'x

  VariableList vars{Symbol("x")};

  // Given: A function body that is just a reference to the variable 'x

  NodePtr func_body = core::list(
      create_node(Symbol("refer")),
      create_node(Symbol("x")),
      core::list(
          create_node(Symbol("return"))
      )
  );

  // Given: A Closure that is constructed with these items

  Closure variadic(env, func_body, vars, nullptr, nullptr, true);

  // Given: A ValueRib containing the strings "Hello" "World" "Leaders"

  ValueRib vr{
      create_node(String("Hello")),
      create_node(String("World")),
      create_node(String("Leaders"))
  };

  // When: You extend the Closure's environment with the ValueRib

  variadic.extend_environment(vr);

  // Then: The environment referred to by the Closure will hold a list of
  // the strings

  ASSERT_EQ(
      variadic.get_environment()->get_value(Symbol("x"))->get_type(),
      Data::Type::DATA_PAIR
  );

  ASSERT_EQ(
    variadic.get_environment()->
        get_value(Symbol("x"))->get<DataPair>().car()->get<String>(),
    String("Hello")
  );

  ASSERT_EQ(
    core::length((variadic.get_environment()->get_value(Symbol("x")))),
    static_cast<int>(3)
  );

}

