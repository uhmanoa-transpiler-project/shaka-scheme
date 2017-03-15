#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "parser/rule_number.h"

/// @brief Tests whether we can parse a single integer.
TEST(Parser_integer, single_integer) {
    std::stringstream iss ("123");
    std::string temp;

    bool b = shaka::parser::rule::integer
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
        auto b = shaka::parser::rule::integer
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


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
