//
// Created by Kirsten on 4/25/2018.
//

#include <gmock/gmock.h>
#include <iostream>
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"

/**
 * @Test: mark_expression() functionality
 */

TEST(GCMarkExpressionTest, mark_expression) {

    // Given: You have constructed a GC and bound it to create_node

    shaka::gc::GC garbage_collector;
    shaka::gc::init_create_node(garbage_collector);

    // Given: Expression constructor created

    shaka::Symbol instruction("halt");
    shaka::Data instruction_data(instruction);
    shaka::DataPair instruction_pair(instruction_data);
    shaka::NodePtr exp = shaka::create_node(instruction_pair);

    // Then: The number of objects in the GC's managed memory is 9

    ASSERT_EQ(garbage_collector.get_size(), 9);

    // When: You invoke mark_expression, and then run a sweep

    shaka::gc::mark_expression(exp);
    garbage_collector.sweep();

    // Then: The number of objects in the GC's managed memory becomes 3

    ASSERT_EQ(garbage_collector.get_size(), 3);
}


