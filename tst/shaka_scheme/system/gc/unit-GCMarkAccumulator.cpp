//
// Created by Kirsten on 4/25/2018.
//

#include <gmock/gmock.h>
#include <iostream>
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"

/**
 * @Test: mark_accumulator() functionality
 */

TEST(GCMarkAccumulatorTest, mark_accumulator) {

    // Given: You have constructed a GC and bound it to create_node

    shaka::gc::GC garbage_collector;
    shaka::gc::init_create_node(garbage_collector);

    // Given: Accumulator constructor created

    shaka::Symbol acc_value("result");
    shaka::NodePtr acc = shaka::create_node(acc_value);

    // Then: The number of objects in the GC's managed memory is 1

    ASSERT_EQ(garbage_collector.get_size(), 1);

    // When: You invoke mark_accumulator, and then run a sweep

    shaka::gc::mark_accumulator(acc);
    garbage_collector.sweep();

    // Then: The number of objects in the GC's managed memory stays as 1

    ASSERT_EQ(garbage_collector.get_size(), 1);
}
