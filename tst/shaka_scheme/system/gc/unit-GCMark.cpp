//
// Created by mortrax on 4/16/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"
#include "shaka_scheme/system/core/lists.hpp"

/**
 * @Test: mark_node() functionality on a DataPair
 */
TEST(GCMarkUnitTest, mark_node_pair_structure) {

  // Given: You have constructed a GC and bound it to create_node

  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: You have constructed a complex pair data structure

  shaka::NodePtr sp1_car = shaka::create_node(shaka::Number(5));
  shaka::NodePtr sp1_cdr = shaka::create_node(shaka::Number(4));

  shaka::NodePtr sub_pair1 = shaka::create_node(shaka::DataPair(sp1_car,
                                                                sp1_cdr));

  shaka::NodePtr sp2_car = shaka::create_node(shaka::Symbol("a"));
  shaka::NodePtr sp2_cdr = shaka::create_node(shaka::Symbol("b"));

  shaka::NodePtr sub_pair2 = shaka::create_node(shaka::DataPair(sp2_car,
                                                                sp2_cdr));

  shaka::NodePtr pair = shaka::create_node(shaka::DataPair(sub_pair1,
                                                           sub_pair2));

  // Then: The number of objects in the GC's managed memory is 27 due to
  // calls to copy constructors

  ASSERT_EQ(garbage_collector.get_size(), 27);

  // When: You initiate a mark starting at pair, and then run a sweep

  shaka::gc::mark_node(pair);
  garbage_collector.sweep();

  // Then: The number of objects in the GC's managed memeory is now 7
  // reflecting the 7 explicit calls to create_node() made in this test

  ASSERT_EQ(garbage_collector.get_size(), 7);

}

/**
 * @Test: mark_node() functionality on a DataPair with cyclic reference
 */

TEST(GCMarkUnitTest, mark_node_cyclic_pair_structure) {

  // Given: You have constructed a GC and bound it to create_node
  shaka::gc::GC garbage_collector;

  shaka::gc::init_create_node(garbage_collector);

  // Given: You have constructed a cyclic pair structure

  shaka::NodePtr p1_car = shaka::create_node(shaka::Number(1));

  shaka::NodePtr p1 = shaka::create_node(shaka::DataPair(p1_car));

  shaka::NodePtr p2_car = shaka::create_node(shaka::Number(2));

  shaka::NodePtr p2 = shaka::create_node(shaka::DataPair(p2_car));

  p1->get<shaka::DataPair>().set_cdr(p2);
  p2->get<shaka::DataPair>().set_cdr(p1);

  // Then: The number of objects in the GC's managed memory is now 14,
  // due to multiple copy constructor calls behind the scenes

  ASSERT_EQ(garbage_collector.get_size(), 14);

  // When: You initiate a mark() starting at p1, followed by a sweep()

  mark_node(p1);
  garbage_collector.sweep();

  // Then: The number of objects in the GC's managed memory is now 4,
  // reflecting the explicit calls to create_node made in this test

  ASSERT_EQ(garbage_collector.get_size(), 4);

}

/**
 * @Test: mark_node() functionality on a Closure
 */

TEST(GCMarkUnitTest, mark_closure_object) {
  // Given: You have constructed a GC object and bound it to create_node()
  shaka::gc::GC garbage_collector;

  shaka::gc::init_create_node(garbage_collector);

  // Given: You have constructed a Closure object representing
  // (lambda (x) (* 2 x))

  shaka::Expression body = shaka::core::list(
      shaka::create_node(shaka::Symbol("refer")),
      shaka::create_node(shaka::Symbol("x")),
      shaka::core::list(
          shaka::create_node(shaka::Symbol("argument")),
          shaka::core::list(
              shaka::create_node(shaka::Symbol("constant")),
              shaka::create_node(shaka::Number(2)),
              shaka::core::list(
                  shaka::create_node(shaka::Symbol("argument")),
                  shaka::core::list(
                      shaka::create_node(shaka::Symbol("refer")),
                      shaka::create_node(shaka::Symbol("*")),
                      shaka::core::list(
                          shaka::create_node(shaka::Symbol("apply"))
                      )
                  )
              )
          )
      )
  );

  shaka::EnvPtr env = std::make_shared<shaka::Environment>(nullptr);
  shaka::VariableList vl{shaka::Symbol("x")};
  shaka::Closure c(env, body, vl, nullptr, nullptr, 1);
  shaka::NodePtr closure_node = shaka::create_node(c);

  // When: You call mark and sweep

  shaka::gc::mark_node(closure_node);

  garbage_collector.sweep();

  // Then: The number of objects in the GC's managed memory is 30

  ASSERT_EQ(garbage_collector.get_size(), 30);

  // Then: The closure object should still be intact

  ASSERT_EQ(closure_node->get<shaka::Closure>().get_variable_list(),
            c.get_variable_list());
}

/**
 * @Test: mark_node() on a shaka::Vector
 */
TEST(GCMarkUnitTest, mark_vector_object) {
  //Given: You have constructed a GC object and bound it to create_node()
  shaka::gc::GC garbage_collector;
  shaka::gc::init_create_node(garbage_collector);

  // Given: You have constructed a shaka::Vector as follows

  shaka::NodePtr node1 = shaka::create_node(shaka::Number(1));
  shaka::NodePtr node2 = shaka::create_node(shaka::Number(2));
  shaka::NodePtr node3 = shaka::create_node(shaka::DataPair(node1, node2));

  shaka::Vector v{node1, node2, node3};

  shaka::NodePtr vector_node = shaka::create_node(v);

  // When: You call mark on vector_node and sweep on the GC
  shaka::gc::mark_node(vector_node);
  garbage_collector.sweep();

  // Then: The number of objects in GC memory is 6

  ASSERT_EQ(garbage_collector.get_size(), 6);

  // Then: The number of objects in vector_node is 3

  ASSERT_EQ(vector_node->get<shaka::Vector>().length(), 3);

}
