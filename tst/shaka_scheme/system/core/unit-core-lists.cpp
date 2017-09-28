//
// Created by aytas on 8/6/2017.
//
#include <gmock/gmock.h>
#include <shaka_scheme/system/core/lists.hpp>



/**
 * @brief Test: Testing (car) for list
 */
TEST(ListsUnitTest, car) {
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
