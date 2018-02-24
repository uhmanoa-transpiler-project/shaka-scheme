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

    shaka::GCList list;

    // Then: You can invoke destructor

    list.~GCList();
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

    // Given: A constructed GCList and 3 GCData on the heap

    shaka::GCList list;

    shaka::GCData *gcd1 = new shaka::GCData(shaka::Data(shaka::Number(1)));
    shaka::GCData *gcd2 = new shaka::GCData(shaka::Data(shaka::Number(2)));
    shaka::GCData *gcd3 = new shaka::GCData(shaka::Data(shaka::Number(3)));

    // When: There are 3 GCData in GCList and you invoke destructor

    list.add_data(gcd1);
    list.add_data(gcd2);
    list.add_data(gcd3);

    list.~GCList();

    // Then: Size of GCList should be 0

    ASSERT_EQ(list.get_size(), 0);
}

/**
 * @Test: Sweep GCList
 */
TEST(GCListUnitTest, sweep_GCList) {

    // Given: A constructed GCList

    // When: There is a GCList of marked and unmarked GCData

    // Then: All unmarked GCData should be deleted, and remaining marked GCData should be unmarked in GCList
}