//
// Created by aytas on 8/6/2017.
//
#include <gmock/gmock.h>
#include <shaka_scheme/system/core/types.hpp>
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"



/**
 * @brief Test: Testing (boolean?)
 */
TEST(TypesUnitTest, is_boolean) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;

  // Given: a boolean node and a null list
  NodePtr node = create_node(Data(Boolean(false)));
  NodePtr null_list_node = create_node(Data());

  // When: you apply the predicate is_boolean()

  // Then: it should be true for a boolean
  ASSERT_TRUE(core::is_boolean(node));
  // Then: it should be false for a non-boolean
  ASSERT_FALSE(core::is_boolean(null_list_node));
}

/**
 * @brief Test: Testing (string?)
 */
TEST(TypesUnitTest, is_string) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;

  // Given: a string node and a null list
  NodePtr node = create_node(Data(String("hi")));
  NodePtr null_list_node = create_node(Data());

  // When: you apply the predicate is_string()

  // Then: it should be true for a string
  ASSERT_TRUE(core::is_string(node));
  // Then: it should be false for a non-string
  ASSERT_FALSE(core::is_string(null_list_node));
}

/**
 * @brief Test: Testing (symbol?)
 */
TEST(TypesUnitTest, is_symbol) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;

  // Given: a symbol node and a null list
  NodePtr node = create_node(Data(Symbol("hi")));
  NodePtr null_list_node = create_node(Data());

  // When: you apply the predicate is_symbol()

  // Then: it should be true for a symbol
  ASSERT_TRUE(core::is_symbol(node));
  // Then: it should be false for a non-symbol
  ASSERT_FALSE(core::is_symbol(null_list_node));
}

/**
 * @brief Test: Testing unspecified(), a special implementation-specific type
 * predicate for detecting "unspecified" values.
 */
TEST(TypesUnitTest, is_unspecified) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;

  // Given: an unspecified value node and a null list
  NodePtr node = core::create_unspecified_node();
  NodePtr null_list_node = create_node(Data());

  // When: you apply the predicate is_unspecified()

  // Then: it should be true for an unspecified value
  ASSERT_TRUE(core::is_unspecified(node));
  // Then: it should be false for a non-unspecified value
  ASSERT_FALSE(core::is_unspecified(null_list_node));
}

/**
 * @brief Test: Testing (eqv?)
 */
TEST(TypesUnitTest, is_eqv) {
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);
  using namespace shaka;

  // Given: two distinct nodes with the same string value.
  NodePtr node1 = create_node(Data(String("hi")));
  NodePtr node2 = create_node(Data(String("hi")));

  // When: you apply the equivalence

  // Then: it should be true for nodes with itself.
  ASSERT_TRUE(core::is_eqv(node1, node1));
  ASSERT_TRUE(core::is_eqv(node2, node2));
  // Then: it should be false for nodes not to themselves.
  ASSERT_FALSE(core::is_eqv(node1, node2));
  ASSERT_FALSE(core::is_eqv(node2, node1));
}
