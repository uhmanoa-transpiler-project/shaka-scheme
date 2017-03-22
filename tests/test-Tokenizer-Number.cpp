#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "parser/Tokenizer.h"
#include "parser/Token.h"
#include "parser/rule_number.h"

#include "Data.h"
#include "DataNode.h"
#include "Procedure.h"
#include "Eval_Expression_impl.h"

TEST(Tokenizer_number, construct) {

	shaka::Token t1(shaka::Token::Type::NUMBER);

}

TEST(Tokenizer_number, compare) {

	shaka::Token t1(shaka::Token::Type::NUMBER, "123");
	shaka::Token t2(shaka::Token::Type::NUMBER, "123");

	ASSERT_EQ(t1, t2);
}

TEST(Tokenizer_number, stringstream) {

	std::stringstream ss ("123");
	shaka::Tokenizer tk(ss);

	shaka::Token t1 = tk.get();
	shaka::Token t2(shaka::Token::Type::NUMBER, "123");

	ASSERT_EQ(t1, t2);


}

TEST(Tokenizer_number, integer_push) {
	std::stringstream ss ("1");
	std::string interm;

	shaka::Tokenizer tk(ss);

	using Node = shaka::DataNode<shaka::Data>;

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

	bool b = shaka::parser::rule::number_integer(tk, root, interm);

	ASSERT_TRUE(b);

	shaka::Number n1 = shaka::get<shaka::Number>
		(*(root -> get_child(0) -> get_data()));

	shaka::Number n2(1);

	ASSERT_EQ(n1, n2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
