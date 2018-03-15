//
// Created by Sean Takafuji on 2/23/2018.
//

#include <gmock/gmock.h>
#include "shaka_scheme/runtime/stdproc/equivalence_predicates.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/vm/Closure.cpp"

TEST(EquivalencePredicatesUnitTest, is_eqv) {
  using Args = std::deque<shaka::NodePtr>;

  Args args = {
      create_node(shaka::Symbol("a")),
      create_node(shaka::Symbol("a")),
//      create_node(shaka::Symbol("b")),
//      create_node(shaka::Number(2)),
//      create_node(shaka::Number(2)),
//      create_node(shaka::Boolean(true)),
//      create_node(shaka::Boolean(true)),
//      create_node(shaka::Boolean(false)),
//      create_node(shaka::Boolean(false)),
  };

  //shaka::VariableList vl;

  shaka::Closure is_eqv_closure(
      std::make_shared<shaka::Callable>(shaka::stdproc::eqv), true);

  Args result = is_eqv_closure.call(args);
  ASSERT_EQ(result[0]->get<shaka::Boolean>(), shaka::Boolean(true));
}

