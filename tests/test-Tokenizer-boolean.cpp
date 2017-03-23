#include "gtest/gtest.h"
#include "parser/Token.h"
#include "parser/Tokenizer.h"

#include <boost/variant.hpp>
#include <string>
#include <sstream>

//TEST(Tokenizer_boolean, constructor_default){
//	shaka::Token(
//		shaka::Token::Type::BOOLEAN,
//		""
//	)
//}

TEST(Tokenizer_boolean, t){
	std::stringstream ss("#t");
	shaka::Tokenizer tk(ss);
	
	ASSERT_EQ(
		tk.get(),
		shaka::Token(
			shaka::Token::Type::BOOLEAN_TRUE,
			"#t"
			)
		);
}

TEST(Tokenizer_boolean, f){
	std::stringstream ss("#f");
	shaka::Tokenizer tk(ss);
}


TEST(Tokenizer_boolean, true){
	std::stringstream ss("#true");
	shaka::Tokenizer tk(ss);
}


TEST(Tokenizer_boolean, constructor){
	std::stringstream ss("#t");
	shaka::Tokenizer tk(ss);
}



int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
