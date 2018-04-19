//
// Created by Jared Shimabukuro on 3/7/18.
//

#include <gmock/gmock.h>
#include "shaka_scheme/system/base/BigInteger.hpp"

/**
 * @brief Test: Default constructor for BigInteger
 */
TEST(BigInteger, test_default_constructor) {
    // Given: a uint64_t vector assigned the value [0]
    std::vector<std::uint64_t> num;
    num.push_back(0);

    // When: a BigInteger is constructed with no arguments
    shaka::BigInteger n0;

    // Then: the string value of the BigInteger should be equal to "0"
    // & the value of the BigInteger should be equal to the given uint64_t vector
    // which is equal to [0]
    ASSERT_EQ(n0.get_str_value(), "0");
    ASSERT_EQ(n0.get_value(), num);
}

/**
 * @brief Test: Copy constructor for BigInteger
 */
TEST(BigInteger, test_copy_constructor) {
    // Given: a BigInteger with
    // string value = "280175720564098589193859415608762087"
    // & value = [280175720564098589, 193859415608762087]
    shaka::BigInteger n1 ("280175720564098589193859415608762087");

    // When: a second BigInteger is constructed by copying the
    // first BigInteger
    shaka::BigInteger n2 (n1);

    // Then: The second BigInteger is equal to the first BigInteger
    ASSERT_EQ(n1, n2);
}

/**
 * @brief Test: Constructor with String input of a positive integer for BigInteger
 */
TEST(BigInteger, test_string_constructor_positive) {
    // Given: a uint64_t vector assigned the value
    // [12, 345678909876543210]
    std::vector<std::uint64_t> num;
    num.push_back(12);
    num.push_back(345678909876543210);

    // When: a BigInteger is constructed constructed with the string input
    // "12345678909876543210"
    shaka::BigInteger n1 ("12345678909876543210");

    // Then: The boolean value for the sign of the BigInteger should be false,
    // The string value of the BigInteger is equal to "12345678909876543210",
    // & the value of the BigInteger is equal to the given uint64_t vector
    // which is equal to [12, 345678909876543210]
    ASSERT_FALSE(n1.get_sign());
    ASSERT_EQ(n1.get_str_value(), "12345678909876543210");
    ASSERT_EQ(n1.get_value(), num);
}

/**
 * @brief Test: Constructor with String input of a negative integer for BigInteger
 */
TEST(BigInteger, test_string_constructor_negative) {
    // Given: a uint64_t vector assigned the value
    // [987654321012, 345678909876543210]
    std::vector<std::uint64_t> num;
    num.push_back(987654321012);
    num.push_back(345678909876543210);

    // When: a BigInteger is constructed constructed with the string input
    // "-987654321012345678909876543210"
    shaka::BigInteger n1 ("-987654321012345678909876543210");

    // Then: The boolean value for the sign of the BigInteger should be true,
    // The string value of the BigInteger is equal to "-987654321012345678909876543210",
    // & the value of the BigInteger is equal to the given uint64_t vector
    // which is equal to [987654321012, 345678909876543210]
    ASSERT_TRUE(n1.get_sign());
    ASSERT_EQ(n1.get_str_value(), "-987654321012345678909876543210");
    ASSERT_EQ(n1.get_value(), num);
}

/**
 * @brief Test: Constructor with Vector input of a positive integer for BigInteger
 */
TEST(BigInteger, test_vector_constructor_positive) {
    // Given: a boolean variable assigned the value 'false'
    // & a uint64_t vector assigned the value
    // [123456789012, 345678909876543210]
    bool sign = false;
    std::vector<std::uint64_t> num;
    num.push_back(123456789012);
    num.push_back(345678909876543210);

    // When: a BigInteger is constructed using the given boolean variable
    // & the given uint64_t vector
    shaka::BigInteger n1 (sign, num);

    // Then: the boolean value for the sign of the BigInteger should be equal
    // to the given boolean variable which is equal to 'false',
    // the value of the BigInteger should be equal to the value of the given
    // uint64_t vector which is equal to [123456789012, 345678909876543210],
    // & the string value of the BigInteger should be equal to
    // "123456789012345678909876543210"
    ASSERT_EQ(n1.get_sign(), sign);
    ASSERT_EQ(n1.get_value(), num);
    ASSERT_EQ(n1.get_str_value(), "123456789012345678909876543210");
}

/**
 * @brief Test: Constructor with Vector input of a negative integer for BigInteger
 */
TEST(BigInteger, test_vector_constructor_negative) {
    // Given: a boolean variable assigned the value 'true'
    // & a uint64_t vector assigned the value
    // [123456789012, 345678909876543210]
    bool sign = true;
    std::vector<std::uint64_t> num;
    num.push_back(123456789012);
    num.push_back(345678909876543210);

    // When: a BigInteger is constructed using the given boolean variable
    // & the given uint64_t vector
    shaka::BigInteger n1 (sign, num);

    // Then: the boolean value for the sign of the BigInteger should be equal
    // to the given boolean variable which is equal to 'false',
    // the value of the BigInteger should be equal to the value of the given
    // uint64_t vector which is equal to [123456789012, 345678909876543210],
    // & the string value of the BigInteger should be equal to
    // "123456789012345678909876543210"
    ASSERT_EQ(n1.get_sign(), sign);
    ASSERT_EQ(n1.get_value(), num);
    ASSERT_EQ(n1.get_str_value(), "-123456789012345678909876543210");
}

/**
 * @brief Test: Constructors for BigInteger given a really, really big number
 */
TEST(BigInteger, test_really_really_big_number) {
    // Given: a BigInteger constructed using a string of a really, really
    // big negative integer
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

    // Given: a Boolean variable assigned the value 'true' &
    // a uint64_t vector assigned sections of a really, really big
    // integer as its value
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

    // When: a second BigInteger is constructed by copying the values
    // of the first BigInteger & a third BigInteger is constructed
    // using the given Boolean value and the given uint64_t vector
    shaka::BigInteger n2(n1);
    shaka::BigInteger n3 (sign, bigNum);

    // Then: the Boolean value of the sign of the first BigInteger should be
    // equal to 'true' & the value of the first BigInteger should be equal
    // to the given uint64_t vector
    ASSERT_TRUE(n1.get_sign());
    ASSERT_EQ(n1.get_value(), bigNum);

    // Then: the first BigInteger should be equal to the second BigInteger
    ASSERT_EQ(n1, n2);

    // Then: the Boolean value of the sign of the third BigInteger should be
    // equal to 'true', the value of the third BigInteger should be equal to
    // the given uint64_t vector, & the string value of the third BigInteger
    // should be equal to the string value of the first BigInteger
    ASSERT_TRUE(n3.get_sign());
    ASSERT_EQ(n3.get_value(), bigNum);
    ASSERT_EQ(n3.get_str_value(), n1.get_str_value());
}

/**
 * @brief Test: Implementation of the Schonage-Strassen Algorithm
 * (Credit to Sanfoundry for the C++ implementation of the Schonage-Strassen Algorithm
 * https://www.sanfoundry.com/cpp-program-implement-schonhage-strassen-algorithm-multiplication-two-numbers/)
 */
TEST(BigInteger, Schonhage_Strassen) {
    std::string num = "1234567890123456789";
    std::uint64_t n1 = 1234567890123456789;
    std::uint64_t n2 = 9876543210987654321;
    shaka::BigInteger n;

    std::string product = n.schonhageStrassen(n1,n2,num.length()+1,num.length()+1);
    ASSERT_EQ(product, "12193263113702179522374638011112635269");

}