#include <iostream>
#include <sstream>

#include <boost/variant.hpp>

#include "gtest/gtest.h"

#include "rule_number_impl.h"

#include "core/base/Data.h"
#include "core/base/DataNode.h"
#include "core/base/Procedure.h"

using namespace shaka;

TEST(Parser_number, pos_integer) {
	std::stringstream ss ("+1");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

	bool b = shaka::parser::rule::number_integer(tk, root, interm);

	ASSERT_TRUE(b);

	DataNode head = *root -> car();

	ASSERT_EQ(DataNode(Number(+1)), head);
	ASSERT_TRUE(root -> is_list());
}

TEST(Parser_number, neg_integer) {
	std::stringstream ss ("-2");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

	bool b = shaka::parser::rule::number_integer(tk, root, interm);

	ASSERT_TRUE(b);

	DataNode head = *root -> car();

	ASSERT_EQ(DataNode(Number(-2)), head);
	ASSERT_TRUE(root -> is_list());
}

TEST(Parser_number, pos_real) {
	std::stringstream ss ("66.99");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

	bool b = shaka::parser::rule::number_real(tk, root, interm);

	ASSERT_TRUE(b);

	DataNode head = *root -> car();

	ASSERT_EQ(DataNode(Number(66.99)), head);
	ASSERT_TRUE(root -> is_list());
}

TEST(Parser_number, neg_real) {
	std::stringstream ss ("-1.23");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

	bool b = shaka::parser::rule::number_real(tk, root, interm);

	ASSERT_TRUE(b);

	DataNode head = *root -> car();

	ASSERT_EQ(DataNode(Number(-1.23)), head);
	ASSERT_TRUE(root -> is_list());
}

TEST(Parser_number, pos_rational) {
	std::stringstream ss ("1/23");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

	bool b = shaka::parser::rule::number_rational(tk, root, interm);

	ASSERT_TRUE(b);

	DataNode head = *root -> car();

	ASSERT_EQ(DataNode(Number(1,23)), head);
	ASSERT_TRUE(root -> is_list());
}

TEST(Parser_number, neg_rational) {
	std::stringstream ss ("-1/23");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

	bool b = shaka::parser::rule::number_rational(tk, root, interm);

	ASSERT_TRUE(b);

	DataNode head = *root -> car();

	ASSERT_EQ(DataNode(Number(-1,23)), head);
	ASSERT_TRUE(root -> is_list());
}

TEST(Parser_number, not_a_number) {
	std::stringstream ss ("abc");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

	bool a = shaka::parser::rule::number_real(tk, root, interm);

	ASSERT_FALSE(a);

	bool b = shaka::parser::rule::number_integer(tk, root, interm);

	ASSERT_FALSE(b);

	bool c = shaka::parser::rule::number_rational(tk, root, interm);

	ASSERT_FALSE(c);
}

TEST(Parser_number, not_a_number_int) {
	std::stringstream ss ("123abc456");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

    	ASSERT_THROW(
		shaka::parser::rule::number_integer(tk, root, interm),
		std::runtime_error
   	 );
}

TEST(Parser_number, not_a_number_real) {
	std::stringstream ss ("123.abc");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

	ASSERT_THROW(
		shaka::parser::rule::number_real(tk, root, interm), 
		std::runtime_error
    	);
}

TEST(Parser_number, not_a_number_rational) {
	std::stringstream ss ("123/abc");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

    	ASSERT_THROW(
		shaka::parser::rule::number_rational(tk, root, interm),
		std::runtime_error
   	);
}

TEST(Parser_number, big_int) {
	std::stringstream ss("2147483648");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

	ASSERT_THROW(
		shaka::parser::rule::number_integer(tk, root, interm),
		std::out_of_range
	);
}

TEST(Parser_number, big_real) {
	std::stringstream ss("0.00000000000000012");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

	ASSERT_THROW(
		shaka::parser::rule::number_integer(tk, root, interm),
		std::out_of_range
	);
}

TEST(Parser_number, big_rational) {
	std::stringstream ss("6969696969696/696969696969696969696969");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<DataNode>(
			shaka::DataNode::list()
	);

	ASSERT_THROW(
		shaka::parser::rule::number_integer(tk, root, interm),
		std::out_of_range
	);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

