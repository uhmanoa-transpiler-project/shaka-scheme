//
// Created by Jared Shimabukuro on 3/7/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/base/BigInteger.hpp"

TEST(BigInteger, test_constructors) {
    shaka::BigInteger n0;
    ASSERT_EQ(n0.get_value(), "0");

    shaka::BigInteger n1 ("12345678909876543210");
    ASSERT_EQ(n1.get_value(), "12345678909876543210");

    shaka::BigInteger n2 (n1);
    ASSERT_EQ(n1, n2);
}

