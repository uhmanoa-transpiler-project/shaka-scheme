#include <sstream>
#include <string>
#include <boost/variant.hpp>
#include <gtest/gtest.h>

#include "core/base/Data.h"
#include "core/base/DataNode.h"
#include "core/base/Procedure.h"
#include "rule_boolean_impl.h"


//////////////////////////////////////////
//		TREE TESTS		//
//////////////////////////////////////////

using namespace shaka;
using Data = shaka::Data;
using NodePtr = std::shared_ptr<shaka::DataNode>;
using EnvPtr = std::shared_ptr<shaka::Environment>;

TEST(DataNode_Boolean, boolean_true) {
	std::stringstream ss0("#t");
	//Initializes tokenizer
	shaka::Tokenizer in0(ss0);
	std::string interm;

	NodePtr root = std::make_shared<DataNode>(DataNode::list());
	EnvPtr env = std::make_shared<Environment>(nullptr);

	//Checks that it goes into my variable function
	ASSERT_TRUE(shaka::parser::rule::boolean(in0, root, interm));
	
	//Checks that there is one child
	ASSERT_EQ(root->length(), 1);

	//Holds the variable of child
	shaka::Boolean a2(true);
	//Use car() to get the first element
	shaka::Boolean a1 = shaka::get<shaka::Boolean>(root->car()->get_data());
	
	ASSERT_EQ(a1, a2);	
}

TEST(DataNode_Boolean, boolean_false) {
	std::stringstream ss0("#f");
	//Initializes tokenizer
	shaka::Tokenizer in0(ss0);
	std::string interm;

	NodePtr root = std::make_shared<DataNode>(DataNode::list());
	EnvPtr env = std::make_shared<Environment>(nullptr);

	//Checks that it goes into my variable function
	ASSERT_TRUE(shaka::parser::rule::boolean(in0, root, interm));
	
	//Checks that there is one child
	ASSERT_EQ(root->length(), 1);

	//Holds the variable of child
	shaka::Boolean a2(false);
	//Use car() to get the first element
	shaka::Boolean a1 = shaka::get<shaka::Boolean>(root->car()->get_data());
	
	ASSERT_EQ(a1, a2);	
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

//see if the node on the tree is a symbol
//if the thing you put on the tree is the same thing as what you passed in
