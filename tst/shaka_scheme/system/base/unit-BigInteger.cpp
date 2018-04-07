//
// Created by Jared Shimabukuro on 3/7/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/base/jshima_BigInteger.hpp"

TEST(BigInteger, test_default_constructor) {
    shaka::BigInteger n0;

    std::vector<std::uint64_t> num;
    num.push_back(0);

    ASSERT_EQ(n0.get_str_value(), "0");
    ASSERT_EQ(n0.get_value(), num);
}

TEST(BigInteger, test_copy_constructor) {
    shaka::BigInteger n1 ("280175720564098589193859415608762087");
    shaka::BigInteger n2 (n1);

    ASSERT_EQ(n1, n2);
}

TEST(BigInteger, test_string_constructor_positive) {
    shaka::BigInteger n1 ("12345678909876543210");
    ASSERT_EQ(n1.get_str_value(), "12345678909876543210");
    ASSERT_FALSE(n1.get_sign());

    std::vector<std::uint64_t> num;
    num.push_back(12);
    num.push_back(345678909876543210);
    ASSERT_EQ(n1.get_value(), num);
}

TEST(BigInteger, test_string_constructor_negative) {
    shaka::BigInteger n1 ("-987654321012345678909876543210");
    ASSERT_EQ(n1.get_str_value(), "-987654321012345678909876543210");
    ASSERT_TRUE(n1.get_sign());

    std::vector<std::uint64_t> num;
    num.push_back(987654321012);
    num.push_back(345678909876543210);
    ASSERT_EQ(n1.get_value(), num);
}

TEST(BigInteger, test_vector_constructor_positive) {
    bool sign = false;
    std::vector<std::uint64_t> num;
    num.push_back(123456789012);
    num.push_back(345678909876543210);
    shaka::BigInteger n1 (sign, num);

    ASSERT_EQ(n1.get_sign(), sign);
    ASSERT_EQ(n1.get_value(), num);
    ASSERT_EQ(n1.get_str_value(), "123456789012345678909876543210");
}

TEST(BigInteger, test_vector_constructor_negative) {
    bool sign = true;
    std::vector<std::uint64_t> num;
    num.push_back(123456789012);
    num.push_back(345678909876543210);
    shaka::BigInteger n1 (sign, num);

    ASSERT_EQ(n1.get_sign(), sign);
    ASSERT_EQ(n1.get_value(), num);
    ASSERT_EQ(n1.get_str_value(), "-123456789012345678909876543210");
}


TEST(BigInteger, test_really_really_big_number) {
    shaka::BigInteger n1 ("-1234567890123456789012345678901234567890"
                          "1234567890123456789012345678901234567890"
                          "1234567890123456789012345678901234567890"
                          "1234567890123456789012345678901234567890"
                          "1234567890123456789012345678901234567890"
                          "1234567890123456789012345678901234567890"
                          "1234567890123456789012345678901234567890"
                          "1234567890123456789012345678901234567890"
                          "1234567890123456789012345678901234567890"
                          "1234567890123456789012345678901234567890"
                          "1234567890123456789012345678901234567890"
                          "12345678901234567890");

    ASSERT_TRUE(n1.get_sign());

    shaka::BigInteger n2(n1);
    ASSERT_EQ(n1, n2);

    bool sign = true;
    std::vector<std::uint64_t> bigNum;
    bigNum.push_back(1234567890);
    bigNum.push_back(123456789012345678);
    bigNum.push_back(901234567890123456);
    bigNum.push_back(789012345678901234);
    bigNum.push_back(567890123456789012);
    bigNum.push_back(345678901234567890);
    bigNum.push_back(123456789012345678);
    bigNum.push_back(901234567890123456);
    bigNum.push_back(789012345678901234);
    bigNum.push_back(567890123456789012);
    bigNum.push_back(345678901234567890);
    bigNum.push_back(123456789012345678);
    bigNum.push_back(901234567890123456);
    bigNum.push_back(789012345678901234);
    bigNum.push_back(567890123456789012);
    bigNum.push_back(345678901234567890);
    bigNum.push_back(123456789012345678);
    bigNum.push_back(901234567890123456);
    bigNum.push_back(789012345678901234);
    bigNum.push_back(567890123456789012);
    bigNum.push_back(345678901234567890);
    bigNum.push_back(123456789012345678);
    bigNum.push_back(901234567890123456);
    bigNum.push_back(789012345678901234);
    bigNum.push_back(567890123456789012);
    bigNum.push_back(345678901234567890);

    ASSERT_EQ(n1.get_value(), bigNum);

    shaka::BigInteger n3 (sign, bigNum);
    ASSERT_EQ(n3.get_sign(), sign);
    ASSERT_EQ(n3.get_value(), bigNum);
    ASSERT_EQ(n3.get_str_value(), "-1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "12345678901234567890");
}