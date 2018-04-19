//
// Created by mortrax on 4/3/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/base/DataPair.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/gc/GCNode.hpp"

TEST(GCInitUnitTest, test_initialize_create_node) {
  // Given: You have created a GC object

  shaka::gc::GC garbage_collector;

  // When: You invoke init_create_node() with the gc as parameter

  shaka::gc::init_create_node(garbage_collector);

  // When: You use the newly bound create_node to create a Data

  shaka::NodePtr number = shaka::create_node(shaka::Data(shaka::Number(5)));

  // Then: The GC object will reflect that you have used it to make an object

  ASSERT_EQ(garbage_collector.get_size(), 1);

  // Then: You can get the Number out of the NodePtr just as you would have
  // before

  ASSERT_EQ(number->get<shaka::Number>(), shaka::Number(5));
}