//
// Created by Kayla Kwock on 3/18/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/runtime/stdproc/pairs_and_lists.hpp"

#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"

/**
 * @brief Tests the is-pair? function
 */
TEST(PairsAndListsUnitTest, is_pair) {
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: numeric arguments 5 and 5
  Args pair {
      shaka::create_node(shaka::DataPair(
          shaka::create_node(shaka::Number(5)),
          shaka::create_node(shaka::Number(5)))
      )
  };

  // When: you give the argument to is_pair
  shaka::NodePtr result {shaka::create_node(shaka::Boolean(
      shaka::stdproc::impl::is_pair(pair)[0]->get<shaka::Boolean>()))};

  // Then: result returns true
  ASSERT_EQ(result->get<shaka::Boolean>(), shaka::Boolean(true));
}

/**
 * @brief Tests the cons function
 */
TEST(PairsAndListsUnitTest, cons) {
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

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

  Args result{shaka::stdproc::impl::cons(pair1)};

  ASSERT_EQ(result[0]->get<shaka::DataPair>().car()->get<shaka::Number>(),
            pair2->get<shaka::DataPair>().car()->get<shaka::Number>());
}

/**
 * @brief Tests the car function
 */
TEST(PairsAndListsUnitTest, car){
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: arguments of a string and a number
  Args args{
      shaka::create_node(shaka::String("Hello")),
      shaka::create_node(shaka::Number(2))
  };

  // When: the arguments are given to cons
  // Then: returns a DataPair of the arguments
  Args pair {shaka::stdproc::impl::cons(args)};

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

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: a string and a numeric argument
  Args args {
      shaka::create_node(shaka::String("Hello")),
      shaka::create_node(shaka::Number(2))
  };

  // When: the arguments are given to cons
  // Then: creates a DataPair of the arguments
  Args pair {shaka::stdproc::impl::cons(args)};

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

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: the numeric arguments 1 and 2
  Args args {
      shaka::create_node(shaka::Number(1)),
      shaka::create_node(shaka::Number(2))
  };

  // When: arguments are given to cons
  // Then: creates a DataPair of the arguments

  Args result {shaka::stdproc::impl::cons(args)};

  // Given: the numeric argument 3
  Args setcar {result[0], shaka::create_node(shaka::Number(3))};

  // When: the argument is given to set_car
  // Then: sets the car of DataPair to the numeric argument

  shaka::stdproc::impl::set_car(setcar);

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

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: The numeric arguments 1 and 2
  Args args {
      shaka::create_node(shaka::Number(1)),
      shaka::create_node(shaka::Number(2))
  };

  // When: arguments are given to cons
  // Then: creates a DataPair of the arguments

  Args result {shaka::stdproc::impl::cons(args)};

  // Given: the numeric argument 4
  Args setcdr {result[0], shaka::create_node(shaka::Number(4))};

  // When: the argument is given to set_cdr
  // Then: sets the cdr of DataPair to the numeric argument
  shaka::stdproc::impl::set_cdr(setcdr);

  // When: the DataPair is given to cdr
  // Then: returns the cdr of the DataPair
  shaka::NodePtr ResCar {result[0]->get<shaka::DataPair>().cdr()};
  ASSERT_EQ(ResCar->get<shaka::Number>(), shaka::Number(4));
}

/**
 * @brief Tests the null? function
 */
TEST(PairsAndListsUnitTest, is_null) {
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  Args args{
          shaka::create_node(shaka::Data())
  };
  Args result {shaka::stdproc::impl::is_null(args)};
  ASSERT_EQ(result[0]->get<shaka::Boolean>(), shaka::Boolean(true));
}

/**
 * @brief Tests the list? function
 */
TEST(PairsAndListsUnitTest, is_list){
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  Args args {
      shaka::create_node(shaka::Number(1)),
      shaka::create_node(shaka::Number(2)),
      shaka::create_node(shaka::Number(3))
  };
  Args list {shaka::stdproc::impl::list(args)};

  Args result {shaka::stdproc::impl::is_list(list)};
  ASSERT_EQ(result[0]->get<shaka::Boolean>(), shaka::Boolean(true));
}

/**
 * @brief Tests the make-list function
 */
TEST(PairsAndListsUnitTest, make_list){

  using Args = std::deque<shaka::NodePtr>;
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: an argument of type NUMBER
  Args args {shaka::create_node(shaka::Number(3))};
  Args result {shaka::stdproc::impl::make_list(args)};

  // When: argument is given to (make_list)
  // Then: makes a list of length equal to the value of the argument filled
  // with empty lists
  ASSERT_EQ(result[0]->
      get<shaka::DataPair>().cdr()->
      get<shaka::DataPair>().cdr()->
      get<shaka::DataPair>().car()->
      get_type(), shaka::Data::Type::NULL_LIST);

  // Given: arguments of a number and a string
  Args args1 {shaka::create_node(shaka::Number(3)),
              shaka::create_node(shaka::String("Hello"))};
  Args result1{shaka::stdproc::impl::make_list(args1)};

  // When: arguments are given to (make_list)
  // Then: makes a list of length equal to the number filled with copies of
  // the string
  ASSERT_EQ(result1[0]->
      get<shaka::DataPair>().cdr()->
      get<shaka::DataPair>().cdr()->
      get<shaka::DataPair>().car()->
      get<shaka::String>(), shaka::String("Hello"));

}

/**
 * @brief Tests the list function
 */
TEST(PairsAndListsUnitTest, list){
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: an empty argument list
  Args null_args {};
  // When: (list) is called with that empty argument list
  Args null_result {shaka::stdproc::impl::list(null_args)};

  // Then: the returned list should just be the null list
  ASSERT_EQ(null_result[0]->get_type(), shaka::Data::Type::NULL_LIST);

  Args args {shaka::create_node(shaka::Number(1)),
             shaka::create_node(shaka::Number(2)),
             shaka::create_node(shaka::Number(3))
  };
  Args result {shaka::stdproc::impl::list(args)};
  ASSERT_EQ(result[0]->get<shaka::DataPair>().cdr()->get<shaka::DataPair>()
                .cdr()->get<shaka::DataPair>().car()->get<shaka::Number>(),
            shaka::Number(3));
}

/**
 * @brief Tests the length function
 */
TEST(PairsAndListsUnitTest, length){
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: a set of numbers
  Args args  {shaka::create_node(shaka::Number(1)),
              shaka::create_node(shaka::Number(2)),
              shaka::create_node(shaka::Number(3))};

  // When: (list) is called on the set of numbers
  // Then: a list of the numbers is returned
  Args list {shaka::stdproc::impl::list(args)};

  // When: (length) is called and given the list as an argument
  // Then: the returned value equals the number of elements in the list
  Args result {shaka::stdproc::impl::length(list)};
  ASSERT_EQ(result[0]->get<shaka::Number>(), shaka::Number(3));
}

/**
 * @brief Tests the append function
 */
TEST(PairsAndListsUnitTest, append){
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: no arguments
  Args empty_append_args {};
  // When: no arguments are given to (append)
  // Then: a result of type NULL_LIST is returned
  Args empty_append_res {shaka::stdproc::impl::append(empty_append_args)};
  ASSERT_EQ(empty_append_res[0]->get_type(), shaka::Data::Type::NULL_LIST);

  // Given: a set of numbers
  Args args  {shaka::create_node(shaka::Number(1)),
              shaka::create_node(shaka::Number(2)),
              shaka::create_node(shaka::Number(3))};
  Args list {shaka::stdproc::impl::list(args)};

  Args one_var_append_args {list[0]};

  // When: only a list is given to (append)
  // Then: the list is returned
  Args one_var_append_res {shaka::stdproc::impl::append(one_var_append_args)};
  ASSERT_EQ(one_var_append_res, one_var_append_args);

  // Given: a list and 2 shaka::Number
  Args multi_var_append_args {list[0],
                              shaka::create_node(shaka::Number(4)),
                              shaka::create_node(shaka::Number(5))};

  // Given: a set of shaka::Number in list form
  Args compared_list_args{shaka::create_node(shaka::Number(1)),
                          shaka::create_node(shaka::Number(2)),
                          shaka::create_node(shaka::Number(3)),
                          shaka::create_node(shaka::Number(4)),
                          shaka::create_node(shaka::Number(5))};
  Args compared_list {shaka::stdproc::impl::list(compared_list_args)};

  // When: the args of a list and 2 shaka::Number are given to (append)
  // Then: the returned list is equivalent to a list created of the same args
  Args multi_var_append_res {shaka::stdproc::impl::append
                                 (multi_var_append_args)};
  // Given: arguments of a list and a desired index
  Args multi_res1 {multi_var_append_res[0],
                   shaka::create_node(shaka::Number(0))};
  Args multi_res2 {multi_var_append_res[0],
                   shaka::create_node(shaka::Number(1))};
  Args multi_res3 {multi_var_append_res[0],
                   shaka::create_node(shaka::Number(2))};
  Args multi_res4 {multi_var_append_res[0],
                   shaka::create_node(shaka::Number(3))};
  Args multi_res5 {multi_var_append_res[0],
                   shaka::create_node(shaka::Number(4))};

  Args multi_comp1 {compared_list[0], shaka::create_node(shaka::Number(0))};
  Args multi_comp2 {compared_list[0], shaka::create_node(shaka::Number(1))};
  Args multi_comp3 {compared_list[0], shaka::create_node(shaka::Number(2))};
  Args multi_comp4 {compared_list[0], shaka::create_node(shaka::Number(3))};
  Args multi_comp5 {compared_list[0], shaka::create_node(shaka::Number(4))};

  // When: the 2 lists are compared at the same index
  // Then: they both return the same value
  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(multi_res1))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(multi_comp1))[0]->get<shaka::Number>());
  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(multi_res2))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(multi_comp2))[0]->get<shaka::Number>());
  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(multi_res3))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(multi_comp3))[0]->get<shaka::Number>());
  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(multi_res4))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(multi_comp4))[0]->get<shaka::Number>());

  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(multi_res5))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(multi_comp5))[0]->get<shaka::Number>());
}

/**
 * @brief Tests the reverse function
 */
TEST(PairsAndListsUnitTest, reverse){
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: 2 lists of numbers, one in reverse of the other
  Args args {shaka::create_node(shaka::Number(1)),
             shaka::create_node(shaka::Number(2)),
             shaka::create_node(shaka::Number(3))};
  Args rev_args {shaka::create_node(shaka::Number(3)),
                 shaka::create_node(shaka::Number(2)),
                 shaka::create_node(shaka::Number(1))};

  Args list {shaka::stdproc::impl::list(args)};
  Args rev_list {shaka::stdproc::impl::list(rev_args)};

  Args result {shaka::stdproc::impl::reverse(list)};

  // When: the two lists are compared
  // Then: elements at the same indexes should equal each other
  Args list1 {result[0], shaka::create_node(shaka::Number(0))};
  Args list2 {result[0], shaka::create_node(shaka::Number(1))};
  Args list3 {result[0], shaka::create_node(shaka::Number(2))};

  Args rev_list1 {rev_list[0], shaka::create_node(shaka::Number(0))};
  Args rev_list2 {rev_list[0], shaka::create_node(shaka::Number(1))};
  Args rev_list3 {rev_list[0], shaka::create_node(shaka::Number(2))};

  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(list1))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(rev_list1))[0]->get<shaka::Number>());
  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(list2))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(rev_list2))[0]->get<shaka::Number>());
  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(list3))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(rev_list3))[0]->get<shaka::Number>());

}

/**
 * @brief Tests the list-tail function
 */
TEST(PairsAndListsUnitTest, list_tail){
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: 2 lists, 1-5 and 3-5
  Args list_args {shaka::create_node(shaka::Number(1)),
                  shaka::create_node(shaka::Number(2)),
                  shaka::create_node(shaka::Number(3)),
                  shaka::create_node(shaka::Number(4)),
                  shaka::create_node(shaka::Number(5))};
  Args compare_list_args {shaka::create_node(shaka::Number(3)),
                          shaka::create_node(shaka::Number(4)),
                          shaka::create_node(shaka::Number(5))};
  Args list {shaka::stdproc::list(list_args)};
  Args compare_list {shaka::stdproc::list(compare_list_args)};

  // Given: the number 2
  // When: the 1-5 list and the number 2 is given to (list_ref)
  // Then: returns a new list with the first 2 elements missing
  Args list_tail_args {list[0],
                       shaka::create_node(shaka::Data(shaka::Number(2)))
  };
  Args result {shaka::stdproc::list_tail(list_tail_args)};

  // When: the 3-5 and returned lists are compared
  // Then: elements at the same indexes should equal each other
  Args list1 {result[0], shaka::create_node(shaka::Number(0))};
  Args list2 {result[0], shaka::create_node(shaka::Number(1))};
  Args list3 {result[0], shaka::create_node(shaka::Number(2))};

  Args compare_list1 {compare_list[0], shaka::create_node(shaka::Number(0))};
  Args compare_list2 {compare_list[0], shaka::create_node(shaka::Number(1))};
  Args compare_list3 {compare_list[0], shaka::create_node(shaka::Number
                                                                  (2))};
  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(list1))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(compare_list1))[0]->get<shaka::Number>());
  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(list2))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(compare_list2))[0]->get<shaka::Number>());
  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(list3))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(compare_list3))[0]->get<shaka::Number>());

}

/**
 * @brief Tests the list-ref function
 */
TEST(PairsAndListsUnitTest, list_ref) {
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: a list of arguments
  Args list_args{shaka::create_node(shaka::Number(1)),
                 shaka::create_node(shaka::Number(2)),
                 shaka::create_node(shaka::Number(3)),
                 shaka::create_node(shaka::String("Hello"))};
  Args list{shaka::stdproc::impl::list(list_args)};

  Args to_check1{list[0], shaka::create_node(shaka::Number(0))};
  Args to_check2{list[0], shaka::create_node(shaka::Number(1))};
  Args to_check3{list[0], shaka::create_node(shaka::Number(2))};
  Args to_check4{list[0], shaka::create_node(shaka::Number(3))};

  // When: the list of arguments and a number is given to (list_ref)
  // Then: returns the value in the list at the index of the number
  ASSERT_EQ((shaka::stdproc::impl::list_ref(to_check1))[0]->
      get<shaka::Number>(), shaka::Number(1));
  ASSERT_EQ((shaka::stdproc::impl::list_ref(to_check2))[0]->
      get<shaka::Number>(), shaka::Number(2));
  ASSERT_EQ((shaka::stdproc::impl::list_ref(to_check3))[0]->
      get<shaka::Number>(), shaka::Number(3));
  ASSERT_EQ((shaka::stdproc::impl::list_ref(to_check4))[0]->
      get<shaka::String>(), shaka::String("Hello"));
}

/**
 * @brief Tests the list-set! function
 */
TEST(PairsAndListsUnitTest, list_set){
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: 2 lists, 1,2,10 and 1-3
  Args list_args {shaka::create_node(shaka::Number(1)),
                  shaka::create_node(shaka::Number(2)),
                  shaka::create_node(shaka::Number(10))};
  Args compare_list_args {shaka::create_node(shaka::Number(1)),
                          shaka::create_node(shaka::Number(2)),
                          shaka::create_node(shaka::Number(3))};
  Args list {shaka::stdproc::list(list_args)};
  Args compare_list {shaka::stdproc::list(compare_list_args)};

  // Given: the numbers 2 and 3
  // When: the 1,2,10 list and the numbers 2 and 3 are given to (list_set)
  // Then: returns the list with the third element (10) replaced with a 3
  Args list_set_args {list[0],
                       shaka::create_node(shaka::Data(shaka::Number(3))),
                       shaka::create_node(shaka::Data(shaka::Number(3)))
  };
  Args result {shaka::stdproc::list_set(list_set_args)};

  // When: the 1-3 and returned lists are compared
  // Then: elements at the same indexes should equal each other
  Args list1 {result[0], shaka::create_node(shaka::Number(0))};
  Args list2 {result[0], shaka::create_node(shaka::Number(1))};
  Args list3 {result[0], shaka::create_node(shaka::Number(2))};

  Args compare_list1 {compare_list[0], shaka::create_node(shaka::Number(0))};
  Args compare_list2 {compare_list[0], shaka::create_node(shaka::Number(1))};
  Args compare_list3 {compare_list[0], shaka::create_node(shaka::Number(2))};

  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(list1))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(compare_list1))[0]->get<shaka::Number>());
  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(list2))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(compare_list2))[0]->get<shaka::Number>());
  ASSERT_EQ(
      (shaka::stdproc::impl::list_ref(list3))[0]->get<shaka::Number>(),
      (shaka::stdproc::impl::list_ref(compare_list3))[0]->get<shaka::Number>());

}

/**
 * @brief Tests the list-copy function
 */
TEST(PairsAndListsUnitTest, list_copy) {
  using Args = std::deque<shaka::NodePtr>;

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: a list of numeric arguments
  Args list_args{shaka::create_node(shaka::Number(1)),
                 shaka::create_node(shaka::Number(2)),
                 shaka::create_node(shaka::Number(3))};
  Args list{shaka::stdproc::impl::list(list_args)};

  // When: (list_copy) is called on the list
  // Then: returns a new list that is a replica of the list
  Args copy {shaka::stdproc::impl::list_copy(list)};

  // Given: references to the partial lists
  Args list1_args {list[0], shaka::create_node(shaka::Data(shaka::Number(0)))};
  Args list2_args {list[0], shaka::create_node(shaka::Data(shaka::Number(1)))};
  Args list3_args {list[0], shaka::create_node(shaka::Data(shaka::Number(2)))};
  Args copy1_args {copy[0], shaka::create_node(shaka::Data(shaka::Number(0)))};
  Args copy2_args {copy[0], shaka::create_node(shaka::Data(shaka::Number(1)))};
  Args copy3_args {copy[0], shaka::create_node(shaka::Data(shaka::Number(2)))};

  Args list1 {shaka::stdproc::impl::list_tail(list1_args)};
  Args list2 {shaka::stdproc::impl::list_tail(list2_args)};
  Args list3 {shaka::stdproc::impl::list_tail(list3_args)};
  Args copy1 {shaka::stdproc::impl::list_tail(copy1_args)};
  Args copy2 {shaka::stdproc::impl::list_tail(copy2_args)};
  Args copy3 {shaka::stdproc::impl::list_tail(copy3_args)};

  // When: (set_car) is called on the partial lists with numbers 42 and 84
  // Then: one list should change, while the other remains untouched
  Args list_car {list1[0], shaka::create_node(shaka::Number(42))};
  Args copy_car {copy2[0], shaka::create_node(shaka::Number(84))};

  shaka::stdproc::impl::set_car(list_car);
  shaka::stdproc::impl::set_car(copy_car);

  // When: the lists are compared element-wise
  // Then: each list should have their own unique permutations
  //       original list is (42 2 3), copy is (1 84 3)
  ASSERT_EQ(list1[0]->get<shaka::DataPair>().car()->get<shaka::Number>(),
            shaka::Number(42));
  ASSERT_EQ(copy1[0]->get<shaka::DataPair>().car()->get<shaka::Number>(),
            shaka::Number(1));
  ASSERT_EQ(list2[0]->get<shaka::DataPair>().car()->get<shaka::Number>(),
            shaka::Number(2));
  ASSERT_EQ(copy2[0]->get<shaka::DataPair>().car()->get<shaka::Number>(),
            shaka::Number(84));
  ASSERT_EQ(list3[0]->get<shaka::DataPair>().car()->get<shaka::Number>(),
            copy3[0]->get<shaka::DataPair>().car()->get<shaka::Number>());
}
