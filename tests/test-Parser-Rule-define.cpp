#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "parser/rule_define.h"

TEST(Parser_rule_define, base) {
    std::stringstream ss("(define x 1)");
    std::string interm;

    // Assert that define x 1 is valid
    ASSERT_TRUE(
            shaka::parser::rule::define(ss, nullptr, interm)
            );
}
TEST(Parser_rule_define, leading_spaces) {
    std::stringstream ss("(        define x 1)");
    std::string interm;

    ASSERT_TRUE(
            shaka::parser::rule::define(ss, nullptr, interm)
            );
}
TEST(Parser_rule_define, inner_spaces) {
    std::stringstream ss("(define     x 1)");
    std::string interm;

    ASSERT_TRUE(
            shaka::parser::rule::define(ss, nullptr, interm)
            );
}
TEST(Parser_rule_define, right_inner_spaces) {
    std::stringstream ss("(define x      1)");
    std::string interm;

    ASSERT_TRUE(
            shaka::parser::rule::define(ss, nullptr, interm)
            );
}
TEST(Parser_rule_define, trailing_spaces) {
    std::stringstream ss("(define x 1         )");
    std::string interm;

    ASSERT_TRUE(
            shaka::parser::rule::define(ss, nullptr, interm)
            );
}
TEST(Parser_rule_define, all_spaces) {
    std::stringstream ss("(  define    x  1)");
    std::string interm;

    ASSERT_TRUE(
            shaka::parser::rule::define(ss, nullptr, interm)
            );
}

TEST(Parser_rule_define, define_misspelled) {
    std::stringstream ss("(defin x 1)");
    std::string interm;

    ASSERT_FALSE(
            shaka::parser::rule::define(ss, nullptr, interm)
            );
}
TEST(Parser_rule_define, missing_left_parenth) {
    std::stringstream ss("define x 1)");
    std::string interm;

    ASSERT_FALSE(
            shaka::parser::rule::define(ss, nullptr, interm)
            );
}





int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
