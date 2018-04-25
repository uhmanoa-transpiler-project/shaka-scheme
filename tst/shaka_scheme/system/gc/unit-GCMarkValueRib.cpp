//
// Created by Kirsten on 4/25/2018.
//

#include <gmock/gmock.h>
#include <iostream>
#include "shaka_scheme/system/gc/GC.hpp"
#include "shaka_scheme/system/gc/init_gc.hpp"

/**
 * @Test: mark_value_rib() functionality
 */

TEST(GCMarkValueRibTest, mark_value_rib) {

    // Given: You have constructed a GC and bound it to create_node

    shaka::gc::GC garbage_collector;
    shaka::gc::init_create_node(garbage_collector);

    // Given: ValueRib constructor created

    shaka::ValueRib vr = {
            shaka::create_node(shaka::String("RVal1")),
            shaka::create_node(shaka::String("RVal2")),
            shaka::create_node(shaka::String("RVal3"))
    };

    // Then: The number of objects in the GC's managed memory is 3

    ASSERT_EQ(garbage_collector.get_size(), 3);

    // When: You invoke mark_value_rib, and then run a sweep

    shaka::gc::mark_value_rib(vr);
    garbage_collector.sweep();

    // Then: The number of objects in the GC's managed memory stays as 3

    ASSERT_EQ(garbage_collector.get_size(), 3);
}

