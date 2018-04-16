//
// Created by aytas on 8/6/2017.
//
#include <gmock/gmock.h>
#include <shaka_scheme/system/core/lists.hpp>

#include <string>
#include <sstream>
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"

/**
 * @brief Test: Testing (car) for list
 */
TEST(ListsUnitTest, car) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;
  // Given: a pair of data put into a NodePtr
  DataPair pair(
      Data(Boolean(true)),  // boolean
      Data()                // null list
  );
  NodePtr node = create_node(Data(pair));

  // When: you examine the pair
  std::cout << *node << std::endl;

  // Then: it should be a proper list and a pair
  ASSERT_TRUE(core::is_proper_list(node));
  ASSERT_TRUE(core::is_pair(node));
  // Then: the car of the pair should be #t
  ASSERT_EQ(core::car(node)->get<Boolean>(), Boolean(true));
}

/**
 * @brief Test: Testing (cdr) for list
 */
TEST(ListsUnitTest, cdr) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;
  // Given: a pair of data put into a NodePtr
  DataPair pair(
      Data(Boolean(true)),  // boolean
      Data(Symbol("foo"))   // symbol
  );
  NodePtr node = create_node(Data(pair));

  // When: you examine the pair
  std::cout << *node << std::endl;

  // Then: it should be a proper list and a pair
  ASSERT_TRUE(core::is_improper_list(node));
  ASSERT_TRUE(core::is_pair(node));
  // Then: The cdr of the pair should be the symbol 'foo
  ASSERT_EQ(core::cdr(node)->get<Symbol>(), Symbol("foo"));
}


/**
 * @brief Test: (cons) for pairs
 */
TEST(ListsUnitTest, cons) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;
  // Given: an arbitrary structure of improper and proper lists
  // '(#t . "Hello world") bar)
  NodePtr node = core::cons(
      core::cons(
          create_node(Data(Boolean(true))),
          create_node(Data(String("Hello world")))
      ),
      core::cons(
        create_node(Data(Symbol("bar"))),
        create_node(Data())
      )
  );

  // When: you examine the list
  std::cout << *node << std::endl;

  // Then: the node should be a proper list
  ASSERT_TRUE(core::is_proper_list(node));
  // Then: the (car node) should be an improper list
  ASSERT_TRUE(core::is_improper_list(core::car(node)));
  // Then: the (cdr node) should be an proper list
  ASSERT_TRUE(core::is_proper_list(core::cdr(node)));
}

/**
 * @brief Test: (list) for lists
 */
TEST(ListsUnitTest, list) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;
  // Given: three symbols
  NodePtr a = create_node(Symbol("a"));
  NodePtr b = create_node(Symbol("b"));
  NodePtr c = create_node(Symbol("c"));

  // When: you create a node from (list a b c)
  NodePtr node = core::list(a, b, c);

  std::cout << *node << std::endl;

  // Then: it should be a list of '(a b c)
  ASSERT_EQ(a->get<Symbol>(), core::car(node)->get<Symbol>());
  ASSERT_EQ(b->get<Symbol>(), core::car(core::cdr(node))->get<Symbol>());
  ASSERT_EQ(c->get<Symbol>(), core::car(core::cdr(core::cdr(node)))->get<Symbol>());
  ASSERT_TRUE(core::is_null_list(core::cdr(core::cdr(core::cdr(node)))));
}

/**
 * @brief Test: (length) for lists
 */
TEST(ListsUnitTest, length_success) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;
  // Given: three symbols
  NodePtr a = create_node(Symbol("a"));
  NodePtr b = create_node(Symbol("b"));
  NodePtr c = create_node(Symbol("c"));

  // When: you create a node from (list a b c)
  NodePtr node = core::list(a, b, c);

  std::cout << *node << std::endl;

  std::cout << static_cast<int>(node->get_type()) << std::endl;
  // Then: the lengths for the list and its cdrs should be correct.
  ASSERT_EQ(core::length(node), 3);
  ASSERT_EQ(core::length(core::cdr(node)), 2);
  ASSERT_EQ(core::length(core::cdr(core::cdr(node))), 1);
  ASSERT_EQ(core::length(core::cdr(core::cdr(core::cdr(node)))), 0);
}

/**
 * @brief Test: (append) with no arguments
 */
TEST(ListsUnitTest, append_0_args_success) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;
  // When: you call (append) with no arguments
  NodePtr node = core::append();
  // Then: it will return a null list
  ASSERT_EQ(node->get_type(), shaka::Data::Type::NULL_LIST);
}

/**
 * @brief Test: (append x) with 1 argument
 */
TEST(ListsUnitTest, append_1_args_success) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;

  // Given: a single node of data
  auto data = create_node(Data(Symbol("hello")));

  // When: you call (append) with 1 argument with that data
  NodePtr node = core::append(data);

  // Then: it will return the data
  ASSERT_EQ(node, data);
}

/**
 * @brief Test: (append list second) for single item
 */
TEST(ListsUnitTest, append_2_args_single_item_success) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;

  // Given: a list of data
  auto data = core::list(
      create_node(Data(Symbol("a"))),
      create_node(Data(Symbol("b"))),
      create_node(Data(Symbol("c")))
  );
  // Given: a second argument
  auto second = create_node(Data(String("hello")));

  // When: you call (append) with 2 argument
  NodePtr node = core::append(data, second);

  // Then: it will return a fresh list with the second appended.
  ASSERT_NE(node, data);

  std::stringstream ss;
  ss << *node;

  // Then: the string output is as follows
  ASSERT_EQ(std::string("(a b c . \"hello\")"), ss.str());
}

/**
 * @brief Test: (append list second) for proper list
 */
TEST(ListsUnitTest, append_2_args_proper_list_success) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;

  // Given: a list of data
  auto data = core::list(
      create_node(Data(Symbol("a"))),
      create_node(Data(Symbol("b"))),
      create_node(Data(Symbol("c")))
  );
  // Given: a second list of data
  auto second = core::list(
      create_node(Data(String("x"))),
      create_node(Data(String("y"))),
      create_node(Data(String("z")))
  );

  // When: you call (append) with 2 argument
  NodePtr node = core::append(data, second);

  // Then: it will return a fresh list with the second appended.
  ASSERT_NE(node, data);

  std::stringstream ss;
  ss << *node;

  // Then: the string output is as follows
  ASSERT_EQ(std::string("(a b c \"x\" \"y\" \"z\")"), ss.str());
}

/**
 * @brief Test: (append list second) for improper list
 */
TEST(ListsUnitTest, append_2_args_improper_list_success) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;

  // Given: a list of data
  auto data = core::list(
      create_node(Data(Symbol("a"))),
      create_node(Data(Symbol("b"))),
      create_node(Data(Symbol("c")))
  );
  // Given: a second improper list of data
  auto second = core::list(
      create_node(Data(String("x"))),
      create_node(Data(String("y")))
  );
  // Placing "z" onto the end of the list in place of '()
  core::set_cdr(core::cdr(second), create_node(Data(String("z"))));

  // When: you call (append) with 2 argument
  NodePtr node = core::append(data, second);

  // Then: it will return a fresh list with the second appended.
  ASSERT_NE(node, data);

  std::stringstream ss;
  ss << *node;

  // Then: the string output is as follows
  ASSERT_EQ(std::string("(a b c \"x\" \"y\" . \"z\")"), ss.str());
}

/**
 * @brief Test: (append list second) for improper list
 */
TEST(ListsUnitTest, append_2_args_first_argument_not_proper_list_failure) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;

  // Given: a first argument that is an improper list
  auto data = core::list(
      create_node(Data(String("x"))),
      create_node(Data(String("y")))
  );
  core::set_cdr(core::cdr(data), create_node(Data(String("z"))));

  // Given: a second argument
  auto second = core::list(
      create_node(Data(Symbol("a"))),
      create_node(Data(Symbol("b"))),
      create_node(Data(Symbol("c")))
  );

  // When: you call (append) with 2 arguments, but with the improper list as
  // the first arugment
  // Then: except a TypeException
  EXPECT_THROW({
    NodePtr node = core::append(data, second);
  }, shaka::TypeException);
}

/**
 * @brief Test: (append list second) for 3 or more arguments
 */
TEST(ListsUnitTest, append_3_args_success) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;

  // Given: a list of data
  auto data = core::list(
      create_node(Data(Symbol("a"))),
      create_node(Data(Symbol("b"))),
      create_node(Data(Symbol("c")))
  );

  auto second = core::list(create_node(Data(Boolean(false))));

  // Given: a third improper list of data
  auto third = core::list(
      create_node(Data(String("x"))),
      create_node(Data(String("y")))
  );
  // Placing "z" onto the end of the list in place of '()
  core::set_cdr(core::cdr(third), create_node(Data(String("z"))));

  // When: you call (append) with 2 argument
  NodePtr node = core::append(data, second, third);

  // Then: it will return a fresh list with the second appended.
  ASSERT_NE(node, data);

  std::stringstream ss;
  ss << *node;

  // Then: the string output is as follows
  ASSERT_EQ(std::string("(a b c #f \"x\" \"y\" . \"z\")"), ss.str());
}
