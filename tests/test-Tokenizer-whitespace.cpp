#include "gtest/gtest.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"

#include <functional>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>

using namespace std;

//1) Construct a string
TEST(Tokenizer_Whitespace, constructor_\t) { 
	shaka::Token tc(shaka::Token::Type::END_OF_FILE, "\t");
}

TEST(Tokenizer_Whitespace, constructor_\n) { 
	shaka::Token tc(shaka::Token::Type::END_OF_FILE, "\n");
}
	
TEST(Tokenizer_Whitespace, constructor_\r) { 
	shaka::Token tc(shaka::Token::Type::END_OF_FILE, "\r");
}

//2) Compare two strings
TEST(Tokenizer_Whitespace, compare) {	
	shaka::Token t1(shaka::Token::Type::END_OF_FILE);
	shaka::Token t2(shaka::Token::Type::END_OF_FILE);

	ASSERT_EQ(t1, t2);
}

//3) String stream
TEST(Tokenizer_Whitespace, string_stream) {
	std::stringstream str("\r");
	shaka::Tokenizer tk(str);
	
	ASSERT_EQ(tk.get(), shaka::Token(shaka::Token::Type::END_OF_FILE));
	
	std::stringstream str1("time");
	shaka::Tokenizer tk1(str1);
	ASSERT_NE(tk1.get(), shaka::Token(shaka::Token::Type::END_OF_FILE));
}

//4) Check
TEST(Tokenizer_Whitespace, check) {

}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

