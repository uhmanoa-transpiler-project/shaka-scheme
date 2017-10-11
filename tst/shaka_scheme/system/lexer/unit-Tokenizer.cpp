#include "shaka_scheme/system/lexer/Tokenizer.hpp"

#include <gmock/gmock.h>

#include <sstream>

TEST(TokenizerUnitTest, number) {
  // Given: a stream with "1" loaded
  std::stringstream ss;
  ss << "1";
  // Given: a Tokenizer getting input from the stream
  shaka::Tokenizer tokenizer(ss);

  // When: you get the next token
  shaka::Token token = tokenizer.get();

  // Then: the next token should be a number with string "1"
  ASSERT_EQ(token.get_type(), shaka::Token::Type::NUMBER);
  ASSERT_EQ(token.get_string(), "1");
}
