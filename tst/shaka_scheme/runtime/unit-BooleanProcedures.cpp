//
// Created by Herman on 2/14/2018.
//

#include <gmock/gmock.h>
#include "shaka_scheme/runtime/stdproc/boolean.hpp"

#include "shaka_scheme/system/base/Number.hpp"
#include "shaka_scheme/system/base/Data.hpp"


TEST(BooleanProceduresUnitTest, notbool) {

  using Args = std::deque<shaka::NodePtr>;;

// Given: Boolean arguments that are true and false

  Args booleant = {create_node(shaka::Boolean(true))};
  Args booleanf = {create_node(shaka::Boolean(false))};
  Args emptylist = {create_node(shaka::Data())};
  Args num0 = {create_node(shaka::Number(0))};
  Args num1 = {create_node(shaka::Number(1))};
  Args string = {create_node(shaka::String("Hello"))};
  Args unspecified = {shaka::create_unspecified()};

// Given: A Native closure constructed with the add procedure

  shaka::VariableList vl;
  shaka::Closure not_closure(nullptr, nullptr, vl,
                           std::make_shared<shaka::Callable>
                               (shaka::stdproc::notbool), nullptr, true);

// When: You call the closure on the arguments

  Args result1 = not_closure.call(booleant);
  Args result2 = not_closure.call(booleanf);
  Args result3 = not_closure.call(emptylist);
  Args result4 = not_closure.call(num0);
  Args result5 = not_closure.call(num1);
  Args result6 = not_closure.call(string);
  Args result7 = not_closure.call(unspecified);

// Then: The result that you get back is False except for the one initally
// with boolean false.

  ASSERT_EQ(result1[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result2[0]->get<shaka::Boolean>(), shaka::Boolean(true));
  ASSERT_EQ(result3[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result4[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result5[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result6[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result7[0]->get<shaka::Boolean>(), shaka::Boolean(false));
}

