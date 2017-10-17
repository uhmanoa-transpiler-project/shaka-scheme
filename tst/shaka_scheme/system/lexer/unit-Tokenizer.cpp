#include "shaka_scheme/system/lexer/Tokenizer.hpp"

#include <gmock/gmock.h>

#include <sstream>

/**
 * @brief Test: parsing a number.
 */
TEST(TokenizerUnitTest, number) {
  // Given: a stream with "1" loaded
  std::stringstream ss;
  ss << "12345.123";
  // Given: a Tokenizer getting input from the stream
  shaka::Tokenizer tokenizer(ss);

  // When: you get the next token
  shaka::Token token = tokenizer.get();

  // Then: the next token should be a number with string "1"
  ASSERT_EQ(token.get_type(), shaka::Token::Type::NUMBER);
  ASSERT_EQ(token.get_string(), "12345.123");
}

/**
 * @brief Test: reading in a (define asdf 1) procedure call
 */
TEST(TokenizerUnitTest, define_procedure_call) {
  // Given: a stringstream initialized with input
  std::stringstream ss("( define\nasdf\t1    )");
  // Given: a Tokenizer initialized with the stringstream
  shaka::Tokenizer tk(ss);

  using shaka::Token;
  // Given: a sequence of tokens to match
  std::vector<shaka::Token> v = {
      {Token::Type::PAREN_START, "("},
      {Token::Type::IDENTIFIER, "define"},
      {Token::Type::IDENTIFIER, "asdf"},
      {Token::Type::NUMBER, "1"},
      {Token::Type::PAREN_END, ")"}
  };

  // When: the Tokenizer reads input into Tokens one by one until end of file
  // Then: the read Tokens should match the expected sequence in v
  int index = 0;
  for (auto t = tk.get();
       t.type != shaka::Token::Type::END_OF_FILE;
       t = tk.get(), ++index) {
    ASSERT_EQ(v[index], t);
  }
}

/**
 * @brief Test: parsing a flawed list sequence with line comment.
 */
TEST(TokenizerUnitTest, flawed_list_and_comment) {
  // Given: an istream with input string
  std::stringstream ss("( \"asdf\" ) ; asdfasdfasdf\n)");
  // Given: a Tokenizer initialized with istream&
  shaka::Tokenizer tokenizer(ss);

  // Type alias for convenience
  using Type = shaka::Token::Type;

  // Given: a sequence of Token to match to
  std::vector<shaka::Token> expected{
      shaka::Token(Type::PAREN_START, "("),
      shaka::Token(Type::STRING, "asdf"),
      shaka::Token(Type::PAREN_END, ")"),
      shaka::Token(Type::PAREN_END, ")")
  };

  std::vector<shaka::Token> input;
  // When: you get and push tokens into the vector while the tokenizer reads
  do {
    shaka::Token t = tokenizer.get();
    if (t != Type::END_OF_FILE) {
      input.push_back(t);
    } else {
      break;
    }
  } while (true);


  // Then: the read-in Tokens should match the expected in v
  for (unsigned i = 0; i < input.size(); ++i) {
    ASSERT_EQ(input[i], expected[i]);
  }
}

/**
 * @brief Test: reading in identifiers
 */
TEST(TokenizerUnitTest, identifiers) {

  using Type = shaka::Token::Type;

  // Given: a stringstream initialized to a string
  std::stringstream ss1("(\t quantifier + / asdf \"qwer\"\n)");

  // Given: a vector of Tokens to match to
  std::vector<shaka::Token> expected = {
      shaka::Token(Type::PAREN_START, "("),
      shaka::Token(Type::IDENTIFIER, "quantifier"),
      shaka::Token(Type::IDENTIFIER, "+"),
      shaka::Token(Type::IDENTIFIER, "/"),
      shaka::Token(Type::IDENTIFIER, "asdf"),
      shaka::Token(Type::STRING, "qwer"),
      shaka::Token(Type::PAREN_END, ")")
  };

  // When: you read in input into Tokens that are inserted into a vectot
  std::vector<shaka::Token> input;
  shaka::Tokenizer tokenizer1(ss1);
  do {
    shaka::Token t = tokenizer1.get();
    if (t != Type::END_OF_FILE) {
      input.push_back(t);
    } else {
      break;
    }
  } while (true);

  // Then: the read-in tokens should match the expected
  for (unsigned i = 0; i < input.size(); ++i) {
    ASSERT_EQ(input[i], expected[i]);
  }
}

/**
 * @brief Test: reading a piped identifier
 */
TEST(TokenizerUnitTest, piped_identifier) {

  // Given: two vectors to hold the expected and input Tokens
  using Type = shaka::Token::Type;
  std::vector<shaka::Token> expected;
  std::vector<shaka::Token> input;

  // Given: a stringstream to use as the basis for input.
  std::stringstream ss2("|asdf\t\n$$|");

  // Given: the expected input
  expected.clear();
  expected = {
      shaka::Token(Type::IDENTIFIER, "asdf\t\n$$"),
  };

  // When: you read in the input Tokens and place them into the input vector
  input.clear();
  shaka::Tokenizer tokenizer2(ss2);
  do {
    shaka::Token t = tokenizer2.get();
    if (t != shaka::Token(Type::END_OF_FILE)) {
      input.push_back(t);
    } else {
      break;
    }
  } while (true);

  // Then: they should match that in expected
  for (unsigned i = 0; i < input.size(); ++i) {
    ASSERT_EQ(input[i], expected[i]);
  }
}

/**
 * @brief Test: commenting and whitespace hash escapes
 */
TEST(TokenizerUnitTest, comment_whitespace_escapes) {
  using Type = shaka::Token::Type;
  // Given: an input stream initialized with a string
  std::stringstream ss3("#\\newline #\\t");

  // Given: a vector of expected Tokens to match to
  std::vector<shaka::Token> expected = {
      shaka::Token(Type::CHARACTER, "\n"),
      shaka::Token(Type::CHARACTER, "t"),
  };

  // When: the input is read into Tokens
  std::vector<shaka::Token> input;
  shaka::Tokenizer tokenizer3(ss3);
  do {
    shaka::Token t = tokenizer3.get();
    if (t != shaka::Token(Type::END_OF_FILE)) {
      input.push_back(t);
    } else {
      break;
    }
  } while (true);

  // Then: the whitespace escape sequences should've been translated into the
  // correct string representations stored within the Token, and match the
  // expected characters.
  for (unsigned i = 0; i < input.size(); ++i) {
    ASSERT_EQ(input[i], expected[i]);
  }

}
