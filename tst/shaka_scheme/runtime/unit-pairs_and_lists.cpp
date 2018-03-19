//
// Created by Kayla Kwock on 3/18/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/runtime/stdproc/pairs_and_lists.hpp"


/**
 * @brief Tests the is-pair? function
 */
TEST(PairsAndListsUnitTest, is_pair) {
  using Args = std::deque<shaka::NodePtr>;

  // Given: numeric arguments 5 and 5
  Args pair {
      shaka::create_node(shaka::DataPair(
          shaka::create_node(shaka::Number(5)),
          shaka::create_node(shaka::Number(5)))
      )
  };

  // When: you give the argument to is_pair
  shaka::NodePtr result {shaka::create_node(shaka::Boolean(
      shaka::stdproc::is_pair(pair)[0]->get<shaka::Boolean>()))};

  // Then: result returns true
  ASSERT_EQ(result->get<shaka::Boolean>(), shaka::Boolean(true));
}

/**
 * @brief Tests the cons function
 */
TEST(PairsAndListsUnitTest, cons) {
  using Args = std::deque<shaka::NodePtr>;

  // Given: numeric arguments 1 and 2 as an Args
  Args pair1{
      shaka::create_node(shaka::Number(1)),
      shaka::create_node(shaka::Number(2))
  };
  // Given: numeric arguments 1 and 2 as a DataPair
  shaka::NodePtr pair2{
      shaka::create_node(shaka::DataPair(
          shaka::create_node(shaka::Number(1)),
          shaka::create_node(shaka::Number(2)))
      )
  };

  // When: you call cons on the Args
  // Then: when car is called on both DataPairs, the results should be the same
  Args result{shaka::stdproc::cons(pair1)};
  ASSERT_EQ(result[0]->get<shaka::DataPair>().car()->get<shaka::Number>(),
            pair2->get<shaka::DataPair>().car()->get<shaka::Number>());
}

/**
 * @brief Tests the car function
 */
TEST(PairsAndListsUnitTest, car){
  using Args = std::deque<shaka::NodePtr>;

  // Given: arguments of a string and a number
  Args args{
      shaka::create_node(shaka::String("Hello")),
      shaka::create_node(shaka::Number(2))
  };

  // When: the arguments are given to cons
  // Then: returns a DataPair of the arguments
  Args pair {shaka::stdproc::cons(args)};

  // When: the DataPair is given to car
  // Then: the car returns the string "Hello"
  shaka::NodePtr result {pair[0]->get<shaka::DataPair>().car()};
  ASSERT_EQ(result->get<shaka::String>(), shaka::String("Hello"));
}

/**
 * @brief Tests the cdr function
 */
TEST(PairsAndListsUnitTest, cdr){
  using Args = std::deque<shaka::NodePtr>;

  // Given: a string and a numeric argument
  Args args {
      shaka::create_node(shaka::String("Hello")),
      shaka::create_node(shaka::Number(2))
  };

  // When: the arguments are given to cons
  // Then: creates a DataPair of the arguments
  Args pair {shaka::stdproc::cons(args)};

  // When: the DataPair is given to cdr
  // Then: returns the number 2
  shaka::NodePtr result{pair[0]->get<shaka::DataPair>().cdr()};
  ASSERT_EQ(result->get<shaka::Number>(), shaka::Number(2));
}

/**
 * @brief Tests the set-car! function
 */
TEST(PairsAndListsUnitTest, set_car){
  using Args = std::deque<shaka::NodePtr>;

  // Given: the numeric arguments 1 and 2
  Args args {
      shaka::create_node(shaka::Number(1)),
      shaka::create_node(shaka::Number(2))
  };

  // When: arguments are given to cons
  // Then: creates a DataPair of the arguments
  Args result {shaka::stdproc::cons(args)};

  // Given: the numeric argument 3
  Args setcar {result[0], shaka::create_node(shaka::Number(3))};

  // When: the argument is given to set_car
  // Then: sets the car of DataPair to the numeric argument
  shaka::stdproc::set_car(setcar);

  // When: the DataPair is given to car
  // Then: returns the car of the DataPair
  shaka::NodePtr ResCar {result[0]->get<shaka::DataPair>().car()};
  ASSERT_EQ(ResCar->get<shaka::Number>(), shaka::Number(3));
}

/**
 * @brief Tests the set-cdr! function
 */
TEST(PairsAndListsUnitTest, set_cdr){
  using Args = std::deque<shaka::NodePtr>;

  // Given: The numeric arguments 1 and 2
  Args args {
      shaka::create_node(shaka::Number(1)),
      shaka::create_node(shaka::Number(2))
  };

  // When: arguments are given to cons
  // Then: creates a DataPair of the arguments
  Args result {shaka::stdproc::cons(args)};

  // Given: the numeric argument 4
  Args setcdr {result[0], shaka::create_node(shaka::Number(4))};

  // When: the argument is given to set_cdr
  // Then: sets the cdr of DataPair to the numeric argument
  shaka::stdproc::set_cdr(setcdr);

  // When: the DataPair is given to cdr
  // Then: returns the cdr of the DataPair
  shaka::NodePtr ResCar {result[0]->get<shaka::DataPair>().cdr()};
  ASSERT_EQ(ResCar->get<shaka::Number>(), shaka::Number(4));
}