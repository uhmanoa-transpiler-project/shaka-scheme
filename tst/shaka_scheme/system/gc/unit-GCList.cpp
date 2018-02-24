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

    // Given: A constructed GCList

    // When: You add 3 GCData to GCList

    // Then: Size of GCList should be 3
}

/**
 * @Test: Destruction of nonempty GCList
 */
TEST(GCListUnitTest, destructor_test_nonempty) {

    // Given: A constructed GCList

    // When: There are 3 GCData in GCList

    // Then: Size of GCList should be 0
}

/**
 * @Test: Sweep GCList
 */
TEST(GCListUnitTest, sweep_GCList) {

    // Given: A constructed GCList

    // When: There is a GCList of marked and unmarked GCData

    // Then: All unmarked GCData should be deleted, and remaining marked GCData should be unmarked in GCList
}