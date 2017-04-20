#include "gtest/gtest.h"
#include "rule_string_impl.h"

#include <boost/variant.hpp>

#include "core/base/Data.h"
#include "core/base/DataNode.h"
#include "core/base/Procedure.h"

#include <string>
#include <sstream>

using namespace shaka;

//using NodePtr = std::shared_ptr<DataNode>;
using EnvPtr = std::shared_ptr<Environment>;

TEST(DataNode_String,make_node){
	std::stringstream ss("\"qwerty\"");
	//Initializes tokenizer
	shaka::Tokenizer in(ss);
	std::string interm;

	//Make shared pointer for root
	NodePtr root = std::make_shared<DataNode>(shaka::DataNode::list());
	EnvPtr env = std::make_shared<Environment>(nullptr);

	//Checks that it goes into my variable function
	ASSERT_TRUE( shaka::parser::rule::string(in,root,interm) );
}

TEST(DataNode_String,is_list){
	std::stringstream ss("\"qwerty\"");
	//Initializes tokenizer
	shaka::Tokenizer in(ss);
	std::string interm;

	//Make shared pointer for root
	NodePtr root = std::make_shared<DataNode>(shaka::DataNode::list());
	EnvPtr env = std::make_shared<Environment>(nullptr);

	shaka::parser::rule::string(in,root,interm);
	
	//Checks that there is one child 
	ASSERT_TRUE(root->is_list());
}

TEST(DataNode_String,length){
	std::stringstream ss("\"qwerty\"");
	//Initializes tokenizer
	shaka::Tokenizer in(ss);
	std::string interm;

	//Make shared pointer for root
	NodePtr root = std::make_shared<DataNode>(shaka::DataNode::list());
	EnvPtr env = std::make_shared<Environment>(nullptr);

	shaka::parser::rule::string(in,root,interm);
	
	//Checks that there is one child 
	ASSERT_EQ(root->length(),1);
}

TEST(DataNode_String,append_to_empty){
	std::stringstream ss("\"qwerty\"");
	//Initializes tokenizer
	shaka::Tokenizer in(ss);
	std::string interm;

	//Make shared pointer for root
	NodePtr root = std::make_shared<DataNode>(shaka::DataNode::list());
	EnvPtr env = std::make_shared<Environment>(nullptr);

	shaka::parser::rule::string(in,root,interm);

	//Holds the variable of child
	shaka::String a2("qwerty");
	
	shaka::String a1 = shaka::get<shaka::String>(root->car()->get_data());

	ASSERT_EQ(a1,a2);
}

TEST(DataNode_String,append_to_not_empty){
	std::stringstream ss1("\"qwerty\"");
	//Initializes tokenizer
	shaka::Tokenizer in1(ss1);
	std::string interm;

	//Make shared pointer for root
	NodePtr root = std::make_shared<DataNode>(shaka::DataNode::list());
	EnvPtr env = std::make_shared<Environment>(nullptr);

	shaka::parser::rule::string(in1,root,interm);
	
	std::stringstream ss2("\"uiop\"");
	//Initializes tokenizer
	shaka::Tokenizer in2(ss2);

	shaka::parser::rule::string(in2,root,interm);
	
	//Holds the variable of child
	shaka::String a2("uiop");
	
	shaka::String a1 = shaka::get<shaka::String>(root->cdr()->get_data());

	ASSERT_EQ(a1,a2);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
