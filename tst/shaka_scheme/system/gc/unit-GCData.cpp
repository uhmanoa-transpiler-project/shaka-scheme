//
// Created by mortrax on 2/20/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/gc/GCData.hpp"
#include "shaka_scheme/system/gc/GC.hpp"

/**
 * @Test: set_next() method of GCData and internal Data state
 */
TEST(GCDataUnitTest, test_set_next) {

    // Given: A GC and you construct two GCData

    shaka::gc::GC garbage_collector;
    shaka::gc::GCData *gcd1 = garbage_collector.create_data(shaka::Number(1));
    shaka::gc::GCData *gcd2 = garbage_collector.create_data(shaka::Number(2));

    // Then: The data in gcd1->next is equal to the data in gcd2

    ASSERT_EQ(gcd2->get_next()->get_data().get<shaka::Number>(),
              gcd1->get_data().get<shaka::Number>());

    ASSERT_EQ(gcd2->get_next()->get_data_address(), gcd1->get_data_address());
}

/**
 * @Test: mark() method of GCData
 */
TEST(GCDataUnitTest, test_mark) {

    // Given: A GC and you construct a GCData object 

    shaka::gc::GC garbage_collector;
    shaka::gc::GCData *gcd = garbage_collector.create_data(shaka::Symbol("mark"));

    // When: You call the mark() method on the object

    gcd->mark();

    // Then: The GCData object will have its mark bit set to true

    ASSERT_TRUE(gcd->is_marked());
}

/**
 * @Test: unmark() method of GCData
 */
TEST(GCDataUnitTest, test_unmark) {

    // Given: A GC and you construct a GCData object 

    shaka::gc::GC garbage_collector;
    shaka::gc::GCData *gcd = garbage_collector.create_data(shaka::Symbol("unmark"));

    // When: You call the mark() and then unmark() methods on the object

    gcd->mark();
    gcd->unmark();

    // Then: The GCData object will have its mark bit set to false

    ASSERT_FALSE(gcd->is_marked());
}
