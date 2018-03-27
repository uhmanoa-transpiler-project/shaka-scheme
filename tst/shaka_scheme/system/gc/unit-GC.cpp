//
// Created by Brandon Wong on 3/26/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/base/Data.hpp"
#include "shaka_scheme/system/gc/GCData.hpp"
#include "shaka_scheme/system/gc/GC.hpp"

/**
 * @Test: Construction of GCData
 */

TEST(GCUnitTest, create_GCData) {

    // Given: A data value and GC object

    shaka::Data data(shaka::Number(1));

    shaka::gc::GC garbage_collector;

    // When: You create a GCData object

    shaka::gc::GCData *gcd = garbage_collector.create_data(data);

    // Then: GCData value should be 1 and size of GCList should be 1

    ASSERT_EQ(gcd->get_data().get<shaka::Number>(), shaka::Number(1));
    ASSERT_EQ(garbage_collector.get_size(), 1);
}