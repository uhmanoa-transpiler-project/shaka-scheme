#include "shaka_scheme/system/lexer/Lexer.hpp"

#include <gmock/gmock.h>

#include <sstream>

/**
 * @brief Test: getting a character
 */
TEST(LexerInputUnitTest, get) {
  // Given: a stream with "123\n" loaded
  std::stringstream ss;
  ss << "123\n";
  // Given: a LexerInput getting input from the stream
  shaka::LexerInput in(ss, std::string("test"));

  // When: the stream is still untouched
  // Then: the stream should be at (line, col, pos) == (1, 1, 1)
  ASSERT_EQ(in.lex_info.line, 1);
  ASSERT_EQ(in.lex_info.col, 1);
  ASSERT_EQ(in.lex_info.pos, 1);

  // When: you get the next character
  // Then: the characters should come out the way they come in, with EOF at end.
  ASSERT_EQ(in.get(), '1');

  // When: the stream has been get'd once and the character gotten is not '\n'
  // Then: the stream should be at (line, col, pos) == (1, 2, 2)
  ASSERT_EQ(in.lex_info.line, 1);
  ASSERT_EQ(in.lex_info.col, 2);
  ASSERT_EQ(in.lex_info.pos, 2);

  ASSERT_EQ(in.get(), '2');
  ASSERT_EQ(in.get(), '3');

  // When: the stream has consumed a newline here as the 4th character
  ASSERT_EQ(in.get(), '\n');
  // Then: the stream should be at (line, col, pos) == (2, 1, 5)
  ASSERT_EQ(in.lex_info.line, 2);
  ASSERT_EQ(in.lex_info.col, 1);
  ASSERT_EQ(in.lex_info.pos, 5);

  // When: you are about to consume the end of the input stream
  // Then: the character returned should be EOF.
  ASSERT_EQ(in.get(), EOF);

  // When: you are at the end of the input, and have already read in EOF
  ASSERT_EQ(in.get(), EOF);
  // Then: trying to read more characters will result in EOF.
  ASSERT_EQ(in.get(), EOF);
}

/**
 * @brief Test: peeking a character
 */
TEST(LexerInputUnitTest, peek) {
  // Given: a stream with "123\n" loaded
  std::stringstream ss;
  ss << "123\n";
  // Given: a LexerInput getting input from the stream
  shaka::LexerInput in(ss, std::string("test"));

  const auto before_lex_info = in.lex_info;

  // When: you peek the next token
  // Then: the same tokens should be returned every time.
  ASSERT_EQ(in.peek(), '1');
  ASSERT_EQ(in.peek(), '1');
  ASSERT_EQ(in.peek(), '1');

  // When: you peek N times
  // Then: the LexInfo should remain untouched.
  ASSERT_EQ(before_lex_info, in.lex_info);
}

/**
 * @brief Test: ungetting a character
 */
TEST(LexerInputUnitTest, unget) {
  // Given: a stream loaded with string input
  std::stringstream ss;
  ss << "1\nabc\nabcde\n";
  // Given: a LexerInput getting input from the stream
  shaka::LexerInput in(ss, std::string("<generic input>"));

  auto before_lex_info = in.lex_info;

  // When: you get a token and then try to unget it
  in.unget(in.get());

  // Then: the character should be put back into the stream
  ASSERT_EQ(in.peek(), '1');
  // Then: the LexInfo should be as before if we didn't put back a newline
  ASSERT_EQ(before_lex_info, in.lex_info);


  // Assert: the lex_info should show (line, col, pos) == (1, 1, 1)
  before_lex_info = in.lex_info;
  ASSERT_EQ(before_lex_info, (shaka::LexInfo{1, 1, 1}));

  // Consume the 1.
  in.get();

  // When: you get a newline and then put it back
  before_lex_info = in.lex_info;
  in.unget(in.get());
  // Then: you should get the same lex_info state as before, since we only
  // put back one newline.
  ASSERT_EQ(before_lex_info, in.lex_info);

  // Consume the newline after the 1.
  in.get();

  // When: you try to get two more lines
  before_lex_info = in.lex_info;
  std::string buffer;
  while (in.peek() != '\n') { buffer += in.get(); } buffer += in.get();
  while (in.peek() != '\n') { buffer += in.get(); } buffer += in.get();
  // Then: assert that we actually did get the contents of the next two lines
  ASSERT_EQ(buffer, "abc\nabcde\n");

  // When: you try to unget the entire two lines of length 3 and 5 in the
  // reverse order that it came in
  for (auto it = buffer.rbegin(); it != buffer.rend(); ++it) {
    in.unget(*it);
  }
  // Then: the lex_info should match except for the lex_info.col since it
  // should be 0 according to our recorded semantics
  ASSERT_NE(before_lex_info, in.lex_info);
  ASSERT_EQ(before_lex_info.module_name, in.lex_info.module_name);
  ASSERT_EQ(before_lex_info.line, in.lex_info.line);
  ASSERT_NE(before_lex_info.col, in.lex_info.col);
  ASSERT_EQ(before_lex_info.pos, in.lex_info.pos);
  // Then: while the before_lex_info.col should be 1
  ASSERT_EQ(before_lex_info.col, 1);
  // Then: the unget()'d lex_info should underflow 0 as it it were (0-3) in
  // unsigned arithmetic because we start with 0 after the unget'd second
  // newline, and then we unget 3 more times, decrementing 0 three times
  ASSERT_EQ(in.lex_info.col, 0-3);
}
