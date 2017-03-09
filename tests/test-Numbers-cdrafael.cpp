#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "Number.h"
#include "Integer.h"
#include "Real.h"

#include "parser/rule_number_cdrafael.h"

/// @brief Tests whether we can parse a positive integer and push onto the tree
TEST(Parser_integer, positive_int_push) {
    std::stringstream ss ("123");
    std::string temp;

    using Node = shaka::DataNode<shaka::Data>;

    auto root = std::make_shared<Node>(shaka::MetaTag::LIST);

    bool b = shaka::parser::rule::number_integer
        <std::string>(ss, root, temp);


    ASSERT_TRUE(b);

    shaka::Number n1 = shaka::get<shaka::Number>
	    (*(root->get_child(0)->get_data()));

    shaka::Number n2(123);

    ASSERT_EQ(n1, n2);
}

/*
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
*/ 

/// @brief Tests whether we can parse a negative integer and push onto the tree
TEST(Parser_integer, negative_int_push) {
    std::stringstream ss ("-123");
    std::string temp;

    using Node = shaka::DataNode<shaka::Data>;

    auto root = std::make_shared<Node>(shaka::MetaTag::LIST);

    bool b = shaka::parser::rule::number_integer
        <std::string>(ss, root, temp);


    ASSERT_TRUE(b);

    shaka::Number n1 = shaka::get<shaka::Number>
	    (*(root->get_child(0)->get_data()));

    shaka::Number n2(-123);

    ASSERT_EQ(n1, n2);
}

/// @brief Tests whether we can parse a positive decimal and push onto the tree
TEST(Parser_integer, positive_decimal_push) {
    std::stringstream ss ("123.456");
    std::string temp;

    using Node = shaka::DataNode<shaka::Data>;

    auto root = std::make_shared<Node>(shaka::MetaTag::LIST);

    bool b = shaka::parser::rule::number_real
	    <std::string>(ss, root, temp);

    ASSERT_TRUE(b);

    shaka::Number n1 = shaka::get<shaka::Number>
	    (*(root->get_child(0)->get_data()));

    shaka::Number n2(123.456);

    ASSERT_EQ(n1, n2);
}

/// @brief Tests whether we can parse a negative decimal and push onto the tree
TEST(Parser_integer, negative_decimal_push) {
	std::stringstream ss ("-123.456");
	std::string temp;

	using Node = shaka::DataNode<shaka::Data>;

	auto root = std::make_shared<Node>(shaka::MetaTag::LIST);

	bool b = shaka::parser::rule::number_real
		<std::string>(ss, root, temp);

	ASSERT_TRUE(b);

	shaka::Number n1 = shaka::get<shaka::Number>
		(*(root->get_child(0)->get_data()));

	shaka::Number n2(-123.456);

	ASSERT_EQ(n1, n2);
}

/// @brief Tests whether we can parse a positive fraction and push onto the tree
TEST(Parser_integer, positive_fraction_push) {
    std::stringstream ss ("1/2");
    std::string temp;

    int numer;
    int denom;

    using Node = shaka::DataNode<shaka::Data>;

    auto root = std::make_shared<Node>(shaka::MetaTag::LIST);

    bool b = shaka::parser::rule::number_rational
	    <std::string>(ss, root, temp);

    ASSERT_TRUE(b);

    numer = shaka::get<int> (*root->get_child(0)->get_data());

    denom = shaka::get<int> (*root->get_child(1)->get_data());

    shaka::Number n3(numer,denom);

    shaka::Number n4(1,2);

    ASSERT_EQ(n3, n4);
}

/// @brief Tests whether we can parse a negative fraction and push onto the tree
TEST(Parser_integer, negative_fraction_push) {
    std::stringstream ss ("-123/456");
    std::string temp;

    int numer;
    int denom;

    using Node = shaka::DataNode<shaka::Data>;

    auto root = std::make_shared<Node>(shaka::MetaTag::LIST);

    bool b = shaka::parser::rule::number_rational
	    <std::string>(ss, root, temp);

    ASSERT_TRUE(b);

    numer = shaka::get<int> (*root->get_child(0)->get_data());

    denom = shaka::get<int> (*root->get_child(1)->get_data());

    shaka::Number n3(numer,denom);

    shaka::Number n4(-123,456);

    ASSERT_EQ(n3, n4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
