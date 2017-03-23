#include "gtest/gtest.h"
#include "parser/Token.h"
#include "parser/Tokenizer.h"
#include <string>
#include <sstream>
using namespace std;


TEST(Tokenizer_comment, constructor) {
	shaka::Token(
		shaka::Token::Type::COMMENT_START,
		";"
	);
}

TEST(Tokenizer_comment, stringstream) {
	stringstream ss("#;comment");

	shaka::Tokenizer tk(ss);

	ASSERT_EQ(
		shaka::Token(
			shaka::Token::Type::DATUM_COMMENT,
			"#;"
		),
		tk.get()
	);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


