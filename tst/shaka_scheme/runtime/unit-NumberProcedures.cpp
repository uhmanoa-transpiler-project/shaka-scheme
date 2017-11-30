//
// Created by Billy Wooton on 11/30/17.
//

#include <gmock/gmock.h>
#include "shaka_scheme/runtime/stdproc/numbers_arithmetic.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/vm/Closure.hpp"

/**
 * @brief Test: Built in add procedure functionality
 */
TEST(NumberProceduresUnitTest, add) {
  using Args = std::deque<shaka::NodePtr>;

  // Given: Numeric arguments that are 5 and 7

  Args args = {create_node(shaka::Number(5)), create_node(shaka::Number(7))};

  // Given: A Native closure constructed with the add procedure

  shaka::VariableList vl;
  shaka::Closure add_closure(nullptr, nullptr, vl,
                             std::make_shared<shaka::Callable>
      (shaka::stdproc::add), nullptr, true);

  // When: You call the closure on the arguments

  Args result = add_closure.call(args);

  // Then: The result that you get back is 12

  ASSERT_EQ(result[0]->get<shaka::Number>(), shaka::Number(12));


}

TEST(NumberProceduresUnitTest, multiply) {
  using Args = std::deque<shaka::NodePtr>;

  // Given: Numeric argumetns that are 0.5, 20, and 1/2

  Args args = {
      create_node(shaka::Number(0.5)),
      create_node(shaka::Number(20)),
      create_node(shaka::Number(1, 2))
  };

  // Given: A native closure constructed with the multiply procedure

  shaka::VariableList vl;

  shaka::Closure multiply_closure(
      nullptr, nullptr, vl,
      std::make_shared<shaka::Callable>(shaka::stdproc::mul), nullptr, true
  );

  // When: You call the closure on the arguments

  Args result = multiply_closure.call(args);

  // Then: The result that you get is the Number 5.0

  ASSERT_EQ(result[0]->get<shaka::Number>(), shaka::Number(5.0));
}