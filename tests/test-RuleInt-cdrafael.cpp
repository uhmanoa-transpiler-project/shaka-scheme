#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "Number.h"
#include "Integer.h"
#include "Real.h"

#include "parser/rule_number_cdrafael.h"

/// @brief Tests whether we can parse a single integer.
TEST(Parser_integer, single_integer) {
    std::stringstream iss ("123");
    std::string temp;

    auto b = shaka::parser::rule::number_real
        <std::string>(iss, nullptr, temp);

    ASSERT_TRUE(b);

    ASSERT_EQ(
        std::stoi(temp),
        123
    );
}

/// @brief Tests whether we can parse a list of space-delimited integers.
TEST(Parser_integer, multiple_integers) {
    std::stringstream iss ("123\n 456 \t 789");
    std::vector<int> v = { 123, 456, 789 };
    std::string temp;
    size_t index = 0;

    while (iss && iss.peek() != std::char_traits<shaka::parser::Char>::eof()) {
        auto b = shaka::parser::rule::number_integer
            <std::string>(iss, nullptr, temp);

        ASSERT_TRUE(b);
        ASSERT_EQ(
            std::stoi(temp),
            v[index]
        );
        ++index;

        unsigned buf = 0;
        while(shaka::parser::rule::space<unsigned>(iss, nullptr, buf));

        temp.clear();
    }
}

/// @brief Tests whether we can parse a negative integer.
TEST(Parser_integer, negative_integer) {
    std::stringstream iss ("-123");
    std::string temp;

    auto b = shaka::parser::rule::number_real
        <std::string>(iss, nullptr, temp);

    ASSERT_TRUE(b);

    ASSERT_EQ(
        std::stof(temp),
        static_cast<double>(-123)
    );
}

/// @brief Tests whether we can parse a decinal.
TEST(Parser_integer, decimal) {
    std::stringstream iss ("123.456");
    std::string temp;

    auto b = shaka::parser::rule::number_real
        <std::string>(iss, nullptr, temp);

    ASSERT_TRUE(b);

   ASSERT_EQ(
        shaka::Number(shaka::Real(std::stod(temp))),
        shaka::Number(shaka::Real(123.456))
    ); 
}

/// @brief Tests whether we can parse a negative decinal.
TEST(Parser_integer, negative_decimal) {
    std::stringstream iss ("-1.23");
    std::string temp;

    auto b = shaka::parser::rule::number_real
        <std::string>(iss, nullptr, temp);

    ASSERT_TRUE(b);

    ASSERT_EQ(
        std::stod(temp),
        -1.23
    );
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
