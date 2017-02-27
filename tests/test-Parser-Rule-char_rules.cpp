#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "parser/char_rules.h"

TEST(Parser_char_rules, digit) {

    {
        std::stringstream iss("1");
        std::string temp;

        // Assert that 1 is a digit
        ASSERT_TRUE(
            shaka::parser::rule::digit<std::string>(iss, nullptr, temp)
        );
    }


    {
        std::stringstream iss("0123456789");
        std::string temp;

        // Read until the next character is NOT a digit.
        while (auto good =  
            shaka::parser::rule::digit<std::string>(
                iss, nullptr, temp
            )
        ) {}

        // Make sure that the sum of the numbers
        ASSERT_EQ(std::stoi(temp), std::stoi("0123456789"));
    }
}

TEST(Parser_char_rules, match_char) {
    std::stringstream iss ("(");
    std::string temp;

    auto b = shaka::parser::rule::match_char
        <std::string, '('>(iss, nullptr, temp);

    ASSERT_EQ(
        true,
        b
    );
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
