#include "gtest/gtest.h"
#include "parser/rule_string_impl.h"

#include <boost/variant.hpp>

#include "Data.h"
#include "DataNode.h"
#include "Procedure.h"
#include "Eval_Expression_impl.h"

#include <string>
#include <sstream>

using Data = shaka::Data;
using IDataTree = shaka::IDataNode<Data>;
using DataTree = shaka::DataNode<Data>;
using Environment = shaka::Environment<shaka::String, std::shared_ptr<IDataTree>>;

TEST(Parser_String,make_token){
	std::stringstream ss("\"qwerty\"");
	//Initializes tokenizer
	shaka::Tokenizer in(ss);
	std::string interm;

	//Make shared pointer for root
	std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
	std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

	//Checks that it goes into my variable function
	ASSERT_TRUE( shaka::parser::rule::string(in,root,interm) );
}

TEST(Parser_String,has_children){
	std::stringstream ss("\"qwerty\"");
	//Initializes tokenizer
	shaka::Tokenizer in(ss);
	std::string interm;

	//Make shared pointer for root
	std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
	std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

	shaka::parser::rule::string(in,root,interm);
	
	//Checks that there is one child 
	ASSERT_EQ( root->get_num_children(), 1);
}

TEST(Parser_String,string_tree){
	std::stringstream ss("\"qwerty\"");
	//Initializes tokenizer
	shaka::Tokenizer in(ss);
	std::string interm;

	//Make shared pointer for root
	std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
	std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

	shaka::parser::rule::string(in,root,interm);

	//Holds the variable of child
	shaka::String a2("qwerty");

	shaka::String a1 = shaka::get<shaka::String> (*(root->get_child(0)->get_data()));

	ASSERT_EQ(a1,a2);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
