//(*gcn).get<shaka::Number>()
//
// Created by Kirsten on 2/25/2018.
//
#include <gmock/gmock.h>
#include "shaka_scheme/system/gc/GCData.hpp"
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"

/**
 * @Test: test_arrow_operator
 */
TEST (GCNodeUnitTest, test_constructor) {

  //Given: You constructed a GC and a GCData

  shaka::gc::GC garbage_collector;

  shaka::gc::GCData * gcd = garbage_collector.create_data(shaka::Number(5));

  //When: You wrap the GCData in a GCNode

  shaka::gc::GCNode gcn(gcd);

  //Then: the data in gcn is equal to 5

  ASSERT_EQ(gcn->get<shaka::Number>(), shaka::Number(5));
}

/**
 * @Test: Test dereference operator of GCNode
 */
TEST (GCNodeUnitTest, test_dereference) {

  //Given: You constructed a GC and a GCData

  shaka::gc::GC garbage_collector;

  shaka::gc::GCData * gcd = garbage_collector.create_data(shaka::Number(5));

  //When: You wrap the GCData in a GCNode

  shaka::gc::GCNode gcn(gcd);

  //Then: the data in gcn is equal to 5
  ASSERT_EQ((*gcn).get<shaka::Number>(), shaka::Number(5));
}

/**
 * @Test: Test get() method of GCNode for pointer equivalence
 */
TEST (GCNodeUnitTest, test_get_method) {
  //Given: You have created a garbage collector object

  shaka::gc::GC garbage_collector;

  //Given: You have bound create_node() to this garbage collector

  shaka::gc::init_create_node(garbage_collector);

  //Given: You have created a Data objects with a Number

  shaka::NodePtr num1 = shaka::create_node(shaka::Data(shaka::Number(1)));

  //Given: You have instantiated an environment

  shaka::EnvPtr env = std::make_shared<shaka::Environment>(nullptr);

  //When: You bind num1 in the environment to the symbol 'num1

  env->set_value(shaka::Symbol("num1"), num1);

  //Then: The address of the bound value should equal the address of the object

  ASSERT_TRUE(num1.get() == env->get_value(shaka::Symbol("num1")).get());
}
