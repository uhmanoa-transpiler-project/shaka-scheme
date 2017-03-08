#include <iostream>
#include <sstream>

#include "gtest/gtest.h"
#include "parser/parenthesis.h"

TEST(Parser_parenthesis_rule, match_paren){
	std::stringstream ss ("(");
	std::string interm;

	auto b = shaka::parser::rule::match_paren <std::string, '('>(ss, nullptr, interm);

	ASSERT_EQ(true, b);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
