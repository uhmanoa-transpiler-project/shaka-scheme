//
// Created by Brandon Wong on 4/20/18.
//

#include <gmock/gmock.h>
#include <iostream>
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"

/**
 * @Test: mark_environment() functionality
 */
TEST(GCMarkEnvironmentTest, mark_environment) {

  // Given: You have constructed a GC and bound it to create_node

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: You have constructed a test environment with a symbol/data binding

  shaka::Environment e(nullptr);
  shaka::Symbol key1("x");
  shaka::Symbol key2("y");
  shaka::Symbol key3("z");
  auto value1 = shaka::create_node(shaka::Number(1));
  auto value2 = shaka::create_node(shaka::Number(2));
  auto value3 = shaka::create_node(shaka::Number(3));
  e.set_value(key1, value1);
  e.set_value(key2, value2);
  e.set_value(key3, value3);

  // Then: The number of objects in the GC's managed memory is 3

  ASSERT_EQ(garbage_collector.get_size(), 3);

  // When: You invoke mark_environment, and then run a sweep

  shaka::gc::mark_environment(e);
  garbage_collector.sweep();

  // Then: The number of objects in the GC's managed memory is still 3

  ASSERT_EQ(garbage_collector.get_size(), 3);
}