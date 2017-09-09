//
// Created by aytas on 8/6/2017.
//
#include "shaka_scheme/system/base/DataPair.hpp"
#include "shaka_scheme/system/base/Data.hpp"

#include <gmock/gmock.h>

/**
 * @brief Test: Data with String
 */
TEST(DataPairUnitTest, single_constructor) {
    // Given: Data initialized to a String
    shaka::String str("Hello world");
    shaka::Data data(str);

    // When: Data is used to initialize a DataPair
    shaka::DataPair pair(data);

    // Then: it should work
}
