#include <sstream>
#include <string>
#include <boost/variant.hpp>
#include <gtest/gtest.h>

#include "Data.h"
#include "DataNode.h"
#include "Procedure.h"
#include "Eval_Expression_impl.h"
#include "parser/rule_variable_impl.h"

/// @brief Basic default constructor test
TEST(Tokenizer_variable, constructor) {
    shaka::Token(shaka::Token::Type::IDENTIFIER, "a");
}

TEST(Tokenizer_variable, comparison) {
    shaka::Token t1(shaka::Token::Type::IDENTIFIER);
    shaka::Token t2(shaka::Token::Type::IDENTIFIER);

    ASSERT_EQ(t1, t2);
}

TEST(Tokenizer_variable, string_stream_eq) {
    // Create the std::istream&
    std::stringstream str("abc");
    shaka::Tokenizer tk(str);

    ASSERT_EQ(tk.get().type, shaka::Token(shaka::Token::Type::IDENTIFIER));
}
/*
TEST(Tokenizer_variable, string_stream_ne) {
    std::stringstream str(" ");
    shaka::Tokenizer tk(str);

    ASSERT_NE(tk.get().type, shaka::Token(shaka::Token::Type::IDENTIFIER));
}*/

//////////////////////////////////////////
//		TREE TESTS		//
//////////////////////////////////////////

using Data = shaka::Data;
using IDataTree = shaka::IDataNode<Data>;
using DataTree = shaka::DataNode<Data>;
using Environment = shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Tokenizer_variable, variable_tree) {
	std::stringstream ss("|\na|");
	//Initializes tokenizer
	shaka::Tokenizer in(ss);
	std::string interm;

	//Make shared pointer for root
	std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
	std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

	//Checks that it goes into my variable function
	ASSERT_TRUE( shaka::parser::rule::variable(in, root, interm) );
	
	//Checks that there is one child
	ASSERT_EQ( root->get_num_children(), 1);

	//Holds the variable of child
	shaka::Symbol a2("\na");

	shaka::Symbol a1 = shaka::get<shaka::Symbol> (*(root->get_child(0)->get_data()));

	ASSERT_EQ(a1, a2);
}

///TWO VARIABLES IN A ROW


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

//see if the node on the tree is a symbol
//if the thing you put on the tree is the same thing as what you passed in
