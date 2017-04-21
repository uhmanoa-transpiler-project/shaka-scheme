#include <gtest/gtest.h>
#include <boost/variant.hpp>

//#include "core/base/Data.h"
//#include "core/base/DataNode.h"
//#include "core/base/Procedure.h"
//#include "core/parser/Tokenizer.h"
#include "core/parser/expression.h"

#include <sstream>
#include <iostream>
#include <string>

TEST(Parser_Expression, compiling) {
	ASSERT_TRUE(true);
}

TEST(Parser_Expression_List, simple_list) {
	std::stringstream ss("(define x 1)");
	shaka::Tokenizer in(ss);
	std::string interm;

	ASSERT_TRUE(shaka::parser::expression(in, nullptr, interm));
}

TEST(Parser_Expression_Number, positive_integer) {
	std::stringstream ss("2345");
	shaka::Tokenizer in(ss);
	std::string interm;

	auto root = std::make_shared<shaka::DataNode>(shaka::DataNode::list());
	
	ASSERT_TRUE(shaka::parser::expression(in, root, interm));

	shaka::DataNode head = *root->car();
	ASSERT_EQ(shaka::DataNode(shaka::Number(2345)), head);
}

TEST(Parser_Expression_Number, negative_integer) {
	std::stringstream ss("-6789");
	shaka::Tokenizer in(ss);
	std::string interm;

	auto root = std::make_shared<shaka::DataNode>(shaka::DataNode::list());

	ASSERT_TRUE(shaka::parser::expression(in, root, interm));
	
	shaka::DataNode head = *root->car();
	ASSERT_EQ(shaka::DataNode(shaka::Number(-6789)), head);
}

TEST(Parser_Expression_Number, real) {
	std::stringstream ss("13.37");
	shaka::Tokenizer in(ss);
	std::string interm;

	auto root = std::make_shared<shaka::DataNode>(shaka::DataNode::list());

	ASSERT_TRUE(shaka::parser::expression(in, root, interm));

	shaka::DataNode head = *root->car();
	ASSERT_EQ(shaka::DataNode(shaka::Number(13.37)), head);
}

TEST(Parser_Expression_Number, rational) {
	std::stringstream ss("7/11");
	shaka::Tokenizer in (ss);
	std::string interm;

	auto root = std::make_shared<shaka::DataNode>(shaka::DataNode::list());

	ASSERT_TRUE(shaka::parser::expression(in, root, interm));

	shaka::DataNode head = *root->car();
	ASSERT_EQ(shaka::DataNode(shaka::Number(7,11)), head);
}

TEST(Parser_Expression_String, string) {
	std::stringstream ss("\"abc123#$%\"");
	shaka::Tokenizer in(ss);
	std::string interm;

	auto root = std::make_shared<shaka::DataNode>(shaka::DataNode::list());

	ASSERT_TRUE(shaka::parser::expression(in, root, interm));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
