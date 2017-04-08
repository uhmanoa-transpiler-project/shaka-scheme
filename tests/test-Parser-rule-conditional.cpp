#include "gtest/gtest.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"
#include "parser/rule-conditional.h"

#include "Data.h"
#include "DataNode.h"
#include "IDataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Define.h" 

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using Data = shaka::Data;
using IDataTree = shaka::IDataNode<Data>;
using DataTree = shaka::DataNode<Data>;
using Environment = shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Parser_Rules, conditional_token_constructor) {
	shaka::Token(
		shaka::Token::Type::INVALID,
		"(if (> 3 2) #t #f)"
	);
}

TEST(Parser_Rules, conditional_GT) {
	// Create a stringstream and give it to the Tokenizer
	std::stringstream ss("(if (> 3 2) #t #f)");
	shaka::Tokenizer tk(ss);
	std::string interm;

	ASSERT_TRUE(shaka::parser::rule::conditional<std::string>
			(tk, nullptr, interm));
}

TEST(Parser_Rules, conditional_EQ) {
	std::stringstream ss("(if (= 15 15) #t #f)");
	shaka::Tokenizer tk(ss);
	std::string interm;

	ASSERT_TRUE(shaka::parser::rule::conditional<std::string>
			(tk, nullptr, interm));
}


TEST(Parser_Rules, conditional_tree) {
	std::stringstream ss("(if (> 3 2) #t #f)");
	shaka::Tokenizer tk(ss);
	std::string interm;

	std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
	std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

	ASSERT_TRUE (shaka::parser::rule::conditional<std::string>
			(tk, root, interm));

	ASSERT_EQ(root->get_num_children(), 0);
	auto child = root->get_child(0);
	ASSERT_EQ(child->get_num_children(), 3);

}

TEST(Parser_Rules, conditional_without_alternate) {
	std::stringstream ss("(if (> 3 2) #t)");
	shaka::Tokenizer tk(ss);
	std::string interm;

	std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
	std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);



	ASSERT_TRUE(shaka::parser::rule::conditional<std::string>
			(tk, root, interm));
}

TEST(Parser_Rules, conditional_no_end_parenthesis) {
	std::stringstream ss("(if (= 15 15) #t #f");
	shaka::Tokenizer tk(ss);
	std::string interm;

	std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
	std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

	ASSERT_FALSE(shaka::parser::rule::conditional<std::string>
			(tk, root, interm));
}

TEST(Parser_Rules, conditional_no_alternate_end_parenthesis) {
	std::stringstream ss("(if (= 5 30) #t");
	shaka::Tokenizer tk(ss);
	std::string interm;

	std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
	std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

	ASSERT_FALSE(shaka::parser::rule::conditional<std::string>
			(tk, root, interm));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
