//
// Created by Brandon Wong on 2/18/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/gc/GCList.hpp"
#include "shaka_scheme/system/gc/GC.hpp"

/**
 * @Test: Construction of GCList
 */
TEST(GCListUnitTest, constructor_test) {

    // Given: A constructed GCList

    shaka::gc::GCList list;

    // Then: It is empty
    
    ASSERT_TRUE(list.is_empty());
}

/**
 * @Test: Destruction of empty GCList
 */
TEST(GCListUnitTest, destructor_test_empty) {

    // Given: A constructed GCList

    shaka::gc::GCList *list = new shaka::gc::GCList();

    // Then: You can invoke destructor

    delete list;
}

/**
 * @Test: Add GCData to GCList
 */
TEST(GCListUnitTest, add_GCData) {

    // Given: You constructed a GC

    shaka::gc::GC garbage_collector;

    // When: You use the GC to construct 3 GCData

    garbage_collector.create_data(shaka::Number(1));
    garbage_collector.create_data(shaka::Number(2));
    garbage_collector.create_data(shaka::Number(3));

    // Then: Size of GCList should be 3

    ASSERT_EQ(garbage_collector.get_size(), 3);
}

/**
 * @Test: Sweep GCList
 */

TEST(GCListUnitTest, sweep_GCList) {

    // Given: You constructed a GC and constructed 5 GCData

    shaka::gc::GC garbage_collector;

    shaka::gc::GCData *gcd1 = garbage_collector.create_data(shaka::Number(1));
    shaka::gc::GCData *gcd2 = garbage_collector.create_data(shaka::Number(2));
    shaka::gc::GCData *gcd3 = garbage_collector.create_data(shaka::Number(3));
    shaka::gc::GCData *gcd4 = garbage_collector.create_data(shaka::Number(4));
    shaka::gc::GCData *gcd5 = garbage_collector.create_data(shaka::Number(5));

    // When: There is a GCList of 2 marked and 3 unmarked GCData

    gcd1->unmark();
    gcd2->unmark();
    gcd3->mark();
    gcd4->unmark();
    gcd5->mark();

    // Then: Size of list should be 5

    ASSERT_EQ(garbage_collector.get_size(), 5);

    // When: We invoke the sweep method

    garbage_collector.sweep();

    // Then: All unmarked GCData should be deleted, and size of GCList should
    // be 2

    ASSERT_EQ(garbage_collector.get_size(), 2);
}
