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

}

/**
 * @Test: Sweep GCList
 */
TEST(GCListUnitTest, sweep_GCList) {

    // Given: A constructed GCList

}