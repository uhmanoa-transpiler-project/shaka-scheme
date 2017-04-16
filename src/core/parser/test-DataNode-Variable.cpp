#include <sstream>
#include <string>
#include <boost/variant.hpp>
#include <gtest/gtest.h>

#include "core/base/Data.h"
#include "core/base/DataNode.h"
#include "core/base/Procedure.h"
#include "rule_variable_impl.h"

/// @brief Basic default constructor test
TEST(DataNode_Symbol, constructor) {
    shaka::Token(shaka::Token::Type::IDENTIFIER, "a");
}

TEST(DataNode_Symbol, comparison) {
    shaka::Token t1(shaka::Token::Type::IDENTIFIER);
    shaka::Token t2(shaka::Token::Type::IDENTIFIER);

    ASSERT_EQ(t1, t2);
}

TEST(DataNode_Symbol, string_stream_eq) {
    // Create the std::istream&
    std::stringstream str("abc");
    shaka::Tokenizer tk(str);

    ASSERT_EQ(tk.get().type, shaka::Token(shaka::Token::Type::IDENTIFIER));
}

//////////////////////////////////////////
//		TREE TESTS		//
//////////////////////////////////////////

using namespace shaka;
using Data = shaka::Data;
using NodePtr = std::shared_ptr<shaka::DataNode>;
using EnvPtr = std::shared_ptr<shaka::Environment>;

TEST(DataNode_Symbol, variable_tree) {
	std::stringstream ss0("|\na|");
	//Initializes tokenizer
	shaka::Tokenizer in0(ss0);
	std::string interm;

	NodePtr root = std::make_shared<DataNode>(DataNode::list());
	EnvPtr env = std::make_shared<Environment>(nullptr);

	//Checks that it goes into my variable function
	ASSERT_TRUE(shaka::parser::rule::variable(in0, root, interm));
	
	//Checks that there is one child
	ASSERT_EQ(root->length(), 1);

	//Holds the variable of child
	shaka::Symbol a2("\na");
	//Use car() to get the first element
	shaka::Symbol a1 = shaka::get<shaka::Symbol>(root->car()->get_data());
	
	ASSERT_EQ(a1, a2);


	//Adding another symbol
	std::stringstream ss1("|\nb|");
	shaka::Tokenizer in1(ss1);
	shaka::parser::rule::variable(in1, root, interm);

	ASSERT_EQ(root->length(), 2);

	shaka::Symbol a3("\nb");
	//Use cdr() to get the last element
	shaka::Symbol a4 = shaka::get<shaka::Symbol>(root->cdr()->get_data());
	
	ASSERT_EQ(a3, a4);	
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

//see if the node on the tree is a symbol
//if the thing you put on the tree is the same thing as what you passed in
