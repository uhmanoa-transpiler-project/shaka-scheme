//
// Created by Brandon Wong on 2/18/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/gc/GCList.hpp"

/**
 * @Test: Construction of GCList
 */
TEST(GCListUnitTest, constructor_test) {

    // Given: A constructed GCList

    shaka::GCList list;

    // Then: It is empty
    
    ASSERT_TRUE(list.is_empty());
}

/**
 * @Test: Destruction of empty GCList
 */
TEST(GCListUnitTest, destructor_test_empty) {

    // Given: A constructed GCList

    shaka::GCList *list = new shaka::GCList();

    // Then: You can invoke destructor

    delete list;
}

/**
 * @Test: Add GCData to GCList
 */
TEST(GCListUnitTest, add_GCData) {

    // Given: A constructed GCList and 3 GCData on the heap

    shaka::GCList list;

    shaka::GCData *gcd1 = new shaka::GCData(shaka::Data(shaka::Number(1)));
    shaka::GCData *gcd2 = new shaka::GCData(shaka::Data(shaka::Number(2)));
    shaka::GCData *gcd3 = new shaka::GCData(shaka::Data(shaka::Number(3)));

    // When: You add 3 GCData to GCList

    list.add_data(gcd1);
    list.add_data(gcd2);
    list.add_data(gcd3);

    // Then: Size of GCList should be 3

    ASSERT_EQ(list.get_size(), 3);
}

/**
 * @Test: Destruction of nonempty GCList
 */
TEST(GCListUnitTest, destructor_test_nonempty) {

    // Given: A constructed GCList and 4 GCData on the heap

    shaka::GCList *list = new shaka::GCList();

    shaka::GCData *gcd1 = new shaka::GCData(shaka::Data(shaka::Number(1)));
    shaka::GCData *gcd2 = new shaka::GCData(shaka::Data(shaka::Number(2)));
    shaka::GCData *gcd3 = new shaka::GCData(shaka::Data(shaka::Number(3)));
    shaka::GCData *gcd4 = new shaka::GCData(shaka::Data(shaka::Number(4)));

    // When: There are 4 GCData in GCList

    list->add_data(gcd1);
    list->add_data(gcd2);
    list->add_data(gcd3);
    list->add_data(gcd4);

    // Then: You invoke destructor

    delete list;
}

/**
 * @Test: Sweep GCList
 */

TEST(GCListUnitTest, sweep_GCList) {

    // Given: A constructed GCList and 5 GCData on the heap

    shaka::GCList list;

    shaka::GCData *gcd1 = new shaka::GCData(shaka::Data(shaka::Number(1)));
    shaka::GCData *gcd2 = new shaka::GCData(shaka::Data(shaka::Number(2)));
    shaka::GCData *gcd3 = new shaka::GCData(shaka::Data(shaka::Number(3)));
    shaka::GCData *gcd4 = new shaka::GCData(shaka::Data(shaka::Number(4)));
    shaka::GCData *gcd5 = new shaka::GCData(shaka::Data(shaka::Number(5)));

    // When: There is a GCList of 2 marked and 3 unmarked GCData

    gcd1->unmark();
    gcd2->unmark();
    gcd3->mark();
    gcd4->unmark();
    gcd5->mark();

    list.add_data(gcd1);
    list.add_data(gcd2);
    list.add_data(gcd3);
    list.add_data(gcd4);
    list.add_data(gcd5);

    // Then: Size of list should be 5

    ASSERT_EQ(list.get_size(), 5);

    // When: We invoke the sweep method

    list.sweep();

    // Then: All unmarked GCData should be deleted, and size of GCList should be 2

    ASSERT_EQ(list.get_size(), 2);
}
