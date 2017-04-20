#include "gtest/gtest.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"

#include <boost/variant.hpp>

#include <string>
#include <sstream>

// Create token
TEST(Tokenizer_Character,any_character) {
	std::stringstream any_char("#\A");
	shaka::Tokenizer token(any_char);
}

TEST(Tokenizer_Character,character_name) {
	std::stringstream char_name("backspace");
	shaka::Tokenizer token(char_name);
}

TEST(Tokenizer_Character,hex_scalar_value) {
	std::stringstream hex("#\x124fb");
	shaka::Tokenizer token(hex);
}

// Compare two tokens

// Create token from stringstream


// Check token from stringstream

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
