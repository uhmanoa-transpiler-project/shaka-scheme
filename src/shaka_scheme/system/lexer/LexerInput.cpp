#include "shaka_scheme/system/lexer/LexerInput.hpp"

namespace shaka {

LexerInput::LexerInput(std::istream& in, std::string module_name) :
    in(in),
    lex_info() {
  lex_info.line = 1;
  lex_info.col= 1;
  lex_info.pos = 1;
  lex_info.module_name = module_name;
}

char LexerInput::get() {
  char c = '\0';
  // Get the next character in the input stream.
  if (buffer.empty()) {
    c = in.get();
  } else {
    c = buffer.front();
    buffer.erase(0);
  }
  // Increment the position, line, and column numbers.
  if (c == '\n') {
    lex_info.line++;
    this->last_col_max = lex_info.col;
    lex_info.col = 1;
  } else {
    lex_info.col++;
  }
  lex_info.pos++;
  // Return the next character.
  return c;
}

void LexerInput::unget(char c) {
  if (c == '\n') {
    lex_info.line--;
    lex_info.col = this->last_col_max;
    this->last_col_max = 0;
  } else {
    lex_info.col--;
  }
  lex_info.pos--;
  this->buffer.insert(0, std::string(1, c));
}

char shaka::LexerInput::peek() {
  if (!buffer.empty()) {
    return buffer[0];
  } else {
    return in.peek();
  }
}

} // namespace shaka
