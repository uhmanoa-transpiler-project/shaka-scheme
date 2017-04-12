#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "parser/Tokenizer.h"
#include "parser/Token.h"
#include "parser/rule_number_impl.h"
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

TEST(Tokenizer_number, pos_integer_push) {
	std::stringstream ss ("+1");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

	bool b = shaka::parser::rule::number_integer(tk, root, interm);

	ASSERT_TRUE(b);

	shaka::Number n1 = shaka::get<shaka::Number>
		(*(root -> get_child(0) -> get_data()));

	shaka::Number n2(+1);

	ASSERT_EQ(n1, n2);
}

TEST(Tokenizer_number, neg_integer_push) {
	std::stringstream ss ("-2");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

	bool b = shaka::parser::rule::number_integer(tk, root, interm);

	ASSERT_TRUE(b);

	shaka::Number n1 = shaka::get<shaka::Number>
		(*(root -> get_child(0) -> get_data()));

	shaka::Number n2(-2);

	ASSERT_EQ(n1, n2);
}

TEST(Tokenizer_number, pos_real_push) {
	std::stringstream ss ("+66.99");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

	bool b = shaka::parser::rule::number_real(tk, root, interm);

	ASSERT_TRUE(b);

	shaka::Number n1 = shaka::get<shaka::Number>
		(*(root -> get_child(0) -> get_data()));

	shaka::Number n2(+66.99);

	ASSERT_EQ(n1, n2);
}

TEST(Tokenizer_number, neg_real_push) {
	std::stringstream ss ("-1.23");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

	bool b = shaka::parser::rule::number_real(tk, root, interm);

	ASSERT_TRUE(b);

	shaka::Number n1 = shaka::get<shaka::Number>
		(*(root -> get_child(0) -> get_data()));

	shaka::Number n2(-1.23);

	ASSERT_EQ(n1, n2);
}

TEST(Tokenizer_number, pos_rational_push) {
	std::stringstream ss ("123/456");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

	bool b = shaka::parser::rule::number_rational(tk, root, interm);

	ASSERT_TRUE(b);

	shaka::Number n1 = shaka::get<shaka::Number> 
			(*root -> get_child(0) -> get_data());

	shaka::Number n2(123, 456);

	ASSERT_EQ(n1, n2);
}

TEST(Tokenizer_number, neg_rational_push) {
	std::stringstream ss ("-7/100");

	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

	bool b = shaka::parser::rule::number_rational(tk, root, interm);

	ASSERT_TRUE(b);

	shaka::Number n1 = shaka::get<shaka::Number> 
			(*root -> get_child(0) -> get_data());

	shaka::Number n2(-7, 100);

	ASSERT_EQ(n1, n2);
}


TEST(Tokenizer_number, not_a_number) {
	std::stringstream ss ("abc");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

	bool a = shaka::parser::rule::number_real(tk, root, interm);

	ASSERT_FALSE(a);

	bool b = shaka::parser::rule::number_integer(tk, root, interm);

	ASSERT_FALSE(b);

	bool c = shaka::parser::rule::number_rational(tk, root, interm);

	ASSERT_FALSE(c);
}

TEST(Tokenizer_number, not_a_number_int) {
	std::stringstream ss ("123abc456");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

    	ASSERT_THROW(
		shaka::parser::rule::number_integer(tk, root, interm),
		std::runtime_error
   	 );
}

TEST(Tokenizer_number, not_a_number_real) {
	std::stringstream ss ("123.abc");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

	ASSERT_THROW(
		shaka::parser::rule::number_real(tk, root, interm), 
		std::runtime_error
    	);
}

TEST(Tokenizer_number, not_a_number_rational) {
	std::stringstream ss ("123/abc");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

    	ASSERT_THROW(
		shaka::parser::rule::number_rational(tk, root, interm),
		std::runtime_error
   	);
}

TEST(Tokenizer_number, big_int) {
	std::stringstream ss("2147483648");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

	ASSERT_THROW(
		shaka::parser::rule::number_integer(tk, root, interm),
		std::out_of_range
	);
}

TEST(Tokenizer_number, big_real) {
	std::stringstream ss("0.00000000000000012");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

	ASSERT_THROW(
		shaka::parser::rule::number_integer(tk, root, interm),
		std::out_of_range
	);
}

TEST(Tokenizer_number, big_rational) {
	std::stringstream ss("6969696969696/696969696969696969696969");
	std::string interm;

	shaka::Tokenizer tk(ss);

	auto root = std::make_shared<shaka::parser::Node>(shaka::MetaTag::LIST);

	ASSERT_THROW(
		shaka::parser::rule::number_integer(tk, root, interm),
		std::out_of_range
	);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

