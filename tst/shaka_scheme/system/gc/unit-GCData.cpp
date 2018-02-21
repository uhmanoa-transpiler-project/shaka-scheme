//
// Created by mortrax on 2/20/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/gc/GCData.hpp"

/**
 * @Test: Construction of GCData on the heap
 */
TEST(GCDataUnitTest, test_constructor) {

    // Given: You construct a GCData on the heap as follows

    shaka::GCData *gcd = new shaka::GCData(shaka::Data(shaka::Number(5)));

    // Then: It should contain the number 5, be unmarked, and have a null next

    ASSERT_EQ(gcd->get_data().get<shaka::Number>(), shaka::Number(5));

    ASSERT_FALSE(gcd->is_marked());

    ASSERT_EQ(gcd->get_next(), nullptr);

    delete gcd;
}

/**
 * @Test: set_next() method of GCData and internal Data state
 */
TEST(GCDataUnitTest, test_set_next) {

    // Given: You construct two GCData on the heap as follows

    shaka::GCData *gcd1 = new shaka::GCData(shaka::Data(shaka::Number(1)));
    shaka::GCData *gcd2 = new shaka::GCData(shaka::Data(shaka::Number(2)));

    // When: You set gcd2 as the next node of gcd1

    gcd1->set_next(gcd2);

    // Then: The data in gcd1->next is equal to the data in gcd2

    ASSERT_EQ(gcd1->get_next()->get_data().get<shaka::Number>(),
              gcd2->get_data().get<shaka::Number>());

    ASSERT_EQ(gcd1->get_next()->get_data_address(), gcd2->get_data_address());

    delete gcd1;
    delete gcd2;
}

/**
 * @Test: mark() method of GCData
 */
TEST(GCDataUnitTest, test_mark) {

    // Given: You construct a GCData object on the heap as follows

    shaka::GCData *gcd = new shaka::GCData(shaka::Data(shaka::Symbol("mark")));

    // When: You call the mark() method on the object

    gcd->mark();

    // Then: The GCData object will have its mark bit set to true

    ASSERT_TRUE(gcd->is_marked());

    delete gcd;
}

/**
 * @Test: unmark() method of GCData
 */
TEST(GCDataUnitTest, test_unmark) {

    // Given: You construct a GCData object on the heap as follows

    shaka::GCData *gcd = new shaka::GCData(shaka::Data(shaka::Symbol("unmark")));

    // When: You call the mark() and then unmark() methods on the object

    gcd->mark();
    gcd->unmark();

    // Then: The GCData object will have its mark bit set to false

    ASSERT_FALSE(gcd->is_marked());
}
