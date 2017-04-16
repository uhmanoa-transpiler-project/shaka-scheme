#include <gtest/gtest.h>
#include "core/base/Data.h"

#include "Tokenizer.h"
#include "Token.h"
#include "rule_number.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace shaka;

/// @brief Basic number pair of 1 and 2
TEST(Number_list, constructor) {
	
	DataNode d1(shaka::Number(1));
	DataNode d2(shaka::Number(2));

	DataNode d3 = DataNode::cons(d1, d2);

	ASSERT_TRUE(d1.is_number());
	ASSERT_FALSE(d1.is_pair());

	ASSERT_TRUE(d2.is_number());
	ASSERT_FALSE(d2.is_pair());

	ASSERT_TRUE(d3.is_pair());

}

// @brief Basic test for printing numbers
TEST(Number_list, print) {

	std::stringstream ss;

	DataNode d1(shaka::Number(1,2));
	DataNode d2(shaka::Number(1234564321));
	DataNode d3(shaka::Number(123.456));
	DataNode d4 = DataNode::cons(d1, d2);
	DataNode d5({Number(123)}, {NodePtr(nullptr)});

	// 1/2
	ss << d1;
	ASSERT_EQ(ss.str(), std::string("1/2"));
	ss.str(std::string());

	// 1234564321
	ss << d2;
	ASSERT_EQ(ss.str(), std::string("1234564321"));
	ss.str(std::string());

	// 123.456
	ss << d3;
	ASSERT_EQ(ss.str(), std::string("123.456"));
	ss.str(std::string());

	// (1/2 . 1234564321)
	ss << d4;
	ASSERT_EQ(ss.str(), std::string("(1/2 . 1234564321)"));
	ss.str(std::string());

	// (123)
	ss << d5;
	ASSERT_EQ(ss.str(), std::string("(123)"));

}

//@brief Basic test for checking car and cdr functions
TEST(Number_list, car_and_cdr) {

	DataNode d1({Number(1.23)}, {Number(4.56)});
	ASSERT_TRUE(d1.is_pair());

	DataNode head = *d1.car();
	ASSERT_EQ(head, DataNode(Number(1.23)));

	DataNode tail = *d1.cdr();
	ASSERT_EQ(tail, DataNode(Number(4.56)));
}

// @brief Basic test for a list of (1 2  3)
TEST(Number_list, list) {

	std::stringstream ss;

	DataNode d1 = DataNode::list(Number(1), Number(2), Number(3));

	ss << d1;
	ASSERT_EQ(ss.str(), std::string("(1 2 3)"));

	std::cout << d1 << std::endl;
			
}

TEST(Parser_number, positive_int) {
	std::stringstream ss ("123");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
		shaka::DataNode::list()
	);

	bool b = shaka::parser::rule::number_integer(tk, root, interm);

	ASSERT_TRUE(b);

	DataNode head = *root -> car();

	ASSERT_EQ(DataNode(Number(123)), head);

}

TEST(Parser_number, positive_real) {
	std::stringstream ss ("1.23");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
		shaka::DataNode::list()
	);

	bool b = shaka::parser::rule::number_real(tk, root, interm);

	ASSERT_TRUE(b);

	DataNode head = *root -> car();

	ASSERT_EQ(DataNode(Number(1.23)), head);

}

TEST(Parser_number, positive_rational) {
	std::stringstream ss ("1/2");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
		shaka::DataNode::list()
	);

	bool b = shaka::parser::rule::number_rational(tk, root, interm);

	ASSERT_TRUE(b);

	DataNode head = *root -> car();

	ASSERT_EQ(DataNode(Number(1,2)), head);

}

TEST(Parser_number, negative_int) {
	std::stringstream ss ("-123");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
		shaka::DataNode::list()
	);

	bool b = shaka::parser::rule::number_integer(tk, root, interm);

	ASSERT_TRUE(b);

	DataNode head = *root -> car();

	ASSERT_EQ(DataNode(Number(123)), head);

}

TEST(Parser_number, negative_real) {
	std::stringstream ss ("-1.23");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
		shaka::DataNode::list()
	);

	bool b = shaka::parser::rule::number_real(tk, root, interm);

	ASSERT_TRUE(b);

	DataNode head = *root -> car();

	ASSERT_EQ(DataNode(Number(1.23)), head);

}


TEST(Parser_number, negative_rational) {
	std::stringstream ss ("-1/2");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
		shaka::DataNode::list()
	);

	bool b = shaka::parser::rule::number_rational(tk, root, interm);

	ASSERT_TRUE(b);

	DataNode head = *root -> car() ;

	ASSERT_EQ(DataNode(Number(1, 2)), head);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
