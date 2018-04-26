//
// Created by Sean Takafuji on 2/23/2018.
//

#include <gmock/gmock.h>
#include "shaka_scheme/runtime/stdproc/equivalence_predicates.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/core/lists.hpp"
#include "shaka_scheme/system/vm/Closure.cpp"
#include "shaka_scheme/system/gc/init_gc.hpp"
#include "shaka_scheme/system/gc/GC.hpp"

using namespace shaka;

TEST(EquivalencePredicatesUnitTest, is_eqv) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  using Args = std::deque<shaka::NodePtr>;

  // Given: Various Data Types
  Args test1 = { // (eqv? 'a 'a) #t
      create_node(shaka::Symbol("a")),
      create_node(shaka::Symbol("a"))};

  Args test2 = { // (eqv? 2 2.0) #f
      create_node(shaka::Number(shaka::Integer(2))),
      create_node(shaka::Number(shaka::Real(2.0)))};

  Args test3 = { // (eqv? #f 'nil) #f
      create_node(shaka::Data(shaka::Boolean(false))),
      create_node(shaka::Data())};

  Args test4 = { // (eqv? #t #f) #f
      create_node(shaka::Boolean(true)),
      create_node(shaka::Boolean(false))};

  Args test5 = { // (eqv? p p) #t
      create_node(shaka::String("p")),
      create_node(shaka::String("p"))};

  Args test6 = { // (eqv? 'a 'b) #f
      create_node(shaka::Symbol("a")),
      create_node(shaka::Symbol("b"))};

  Args test7 = { // (eq? '(a, b) '(a,b)) #f
      create_node(shaka::DataPair(shaka::Symbol("a"), shaka::Symbol("b"))),
      create_node(shaka::DataPair(shaka::Symbol("a"), shaka::Symbol("b"))),
  };


  // Given: A Native closure constructed with the eqv? procedure
  shaka::VariableList vl;
  shaka::Closure is_eqv_closure(nullptr, nullptr, vl,
                                std::make_shared<shaka::Callable>
                                    (shaka::stdproc::eqv), nullptr, true);

  // When: Argument 1 is eqv to Argument 2
  Args result1 = is_eqv_closure.call(test1);
  Args result2 = is_eqv_closure.call(test2);
  Args result3 = is_eqv_closure.call(test3);
  Args result4 = is_eqv_closure.call(test4);
  Args result5 = is_eqv_closure.call(test5);
  Args result6 = is_eqv_closure.call(test6);
  Args result7 = is_eqv_closure.call(test7);

  // Then: Each test case should equal the specified boolean value
  ASSERT_EQ(result1[0]->get<shaka::Boolean>(), shaka::Boolean(true));
  ASSERT_EQ(result2[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result3[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result4[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result5[0]->get<shaka::Boolean>(), shaka::Boolean(true));
  ASSERT_EQ(result6[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result7[0]->get<shaka::Boolean>(), shaka::Boolean(false));
}

TEST(EquivalencePredicatesUnitTest, is_eq) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  using Args = std::deque<shaka::NodePtr>;

  // Given: Various Data Types
  Args test1 = { // (eq? 'a 'a) #t
      create_node(shaka::Symbol("a")),
      create_node(shaka::Symbol("a"))
  };

  Args test2 = { // (eq? 2 2.0) #f
      create_node(shaka::Number(shaka::Integer(2))),
      create_node(shaka::Number(shaka::Real(2.0)))
  };

  Args test3 = { // (eq? #f 'nil) #f
      create_node(shaka::Data(shaka::Boolean(false))),
      create_node(shaka::Data())
  };

  Args test4 = { // (eq? #t #f) #f
      create_node(shaka::Boolean(true)),
      create_node(shaka::Boolean(false))
  };

  Args test5 = { // (eq? p p) #t
      create_node(shaka::String("p")),
      create_node(shaka::String("p"))
  };

  Args test6 = { // (eq? 'a 'b) #f
      create_node(shaka::Symbol("a")),
      create_node(shaka::Symbol("b"))
  };

  Args test7 = { // (eq? '(a, b) '(a,b)) #f
      create_node(shaka::DataPair(shaka::Symbol("a"), shaka::Symbol("b"))),
      create_node(shaka::DataPair(shaka::Symbol("a"), shaka::Symbol("b"))),
  };


  // Given: A Native closure constructed with the eq? procedure
  shaka::VariableList vl;
  shaka::Closure is_eq_closure(nullptr, nullptr, vl,
                               std::make_shared<shaka::Callable>
                                   (shaka::stdproc::eq), nullptr, true);

  // When: Argument 1 is eqv to Argument 2
  Args result1 = is_eq_closure.call(test1);
  Args result2 = is_eq_closure.call(test2);
  Args result3 = is_eq_closure.call(test3);
  Args result4 = is_eq_closure.call(test4);
  Args result5 = is_eq_closure.call(test5);
  Args result6 = is_eq_closure.call(test6);
  Args result7 = is_eq_closure.call(test7);

  // Then: Each test case should equal the specified boolean value
  ASSERT_EQ(result1[0]->get<shaka::Boolean>(), shaka::Boolean(true));
  ASSERT_EQ(result2[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result3[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result4[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result5[0]->get<shaka::Boolean>(), shaka::Boolean(true));
  ASSERT_EQ(result6[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result7[0]->get<shaka::Boolean>(), shaka::Boolean(false));
}

TEST(EquivalencePredicatesUnitTest, is_equal) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using Args = std::deque<shaka::NodePtr>;
  const auto& c = shaka::create_node;

  // Given: Various Data Types
  Args test1 = { // (equal? 'a 'a) #t
      create_node(shaka::Symbol("a")),
      create_node(shaka::Symbol("a"))
  };

  Args test2 = { // (equal? 2 2.0) #f
      create_node(shaka::Number(shaka::Integer(2))),
      create_node(shaka::Number(shaka::Real(2.0)))
  };

  Args test3 = { // (equal? #f 'nil) #f
      create_node(shaka::Data(shaka::Boolean(false))),
      create_node(shaka::Data())
  };

  Args test4 = { // (equal? #t #f) #f
      create_node(shaka::Boolean(true)),
      create_node(shaka::Boolean(false))
  };

  Args test5 = { // (equal? p p) #t
      create_node(shaka::String("p")),
      create_node(shaka::String("p"))
  };

  Args test6 = { // (equal? 'a 'b) #f
      create_node(shaka::Symbol("a")),
      create_node(shaka::Symbol("b"))
  };

  Args test7 = { // (equal? '(a, b), '(a, b)) #t
      create_node(shaka::DataPair(shaka::Symbol("a"), shaka::Symbol("b"))),
      create_node(shaka::DataPair(shaka::Symbol("a"), shaka::Symbol("b")))
  };

  Args test8 = { // (equal? '(a, b), '(b, b)) #f
      create_node(shaka::DataPair(shaka::Symbol("a"), shaka::Symbol("b"))),
      create_node(shaka::DataPair(shaka::Symbol("b"), shaka::Symbol("b")))
  };

  Args test9 = { // (equal? '(a, (b), c) '(a, (b), 'c) #t
      shaka::core::list(
        c(shaka::Symbol("a")),
        shaka::core::list(
            c(shaka::Symbol("b"))
        ),
        c(shaka::Symbol("c"))
      ),
      shaka::core::list(
          c(shaka::Symbol("a")),
          shaka::core::list(
              c(shaka::Symbol("b"))
          ),
          c(shaka::Symbol("c"))
      )
  };


  // Given: A Native closure constructed with the eq? procedure
  shaka::VariableList vl;
  shaka::Closure is_equal_closure(nullptr, nullptr, vl,
                                  std::make_shared<shaka::Callable>
                                      (shaka::stdproc::equal), nullptr, true);

  // When: Argument 1 is equal to Argument 2
  Args result1 = is_equal_closure.call(test1);
  Args result2 = is_equal_closure.call(test2);
  Args result3 = is_equal_closure.call(test3);
  Args result4 = is_equal_closure.call(test4);
  Args result5 = is_equal_closure.call(test5);
  Args result6 = is_equal_closure.call(test6);
  Args result7 = is_equal_closure.call(test7);
  Args result8 = is_equal_closure.call(test8);
  Args result9 = is_equal_closure.call(test9);

  // Then: Each test case should equal the specified boolean value
  ASSERT_EQ(result1[0]->get<shaka::Boolean>(), shaka::Boolean(true));
  ASSERT_EQ(result2[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result3[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result4[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result5[0]->get<shaka::Boolean>(), shaka::Boolean(true));
  ASSERT_EQ(result6[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result7[0]->get<shaka::Boolean>(), shaka::Boolean(true));
  ASSERT_EQ(result8[0]->get<shaka::Boolean>(), shaka::Boolean(false));
  ASSERT_EQ(result9[0]->get<shaka::Boolean>(), shaka::Boolean(true));
}

