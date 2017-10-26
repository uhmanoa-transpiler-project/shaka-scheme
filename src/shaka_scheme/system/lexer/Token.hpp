#ifndef SHAKA_LEXER_TOKEN_H
#define SHAKA_LEXER_TOKEN_H

#include "shaka_scheme/system/lexer/LexInfo.hpp"

#include <iostream>
#include <string>

namespace shaka {

struct Token {
public:
  enum class Type : int {
    INVALID = 255,
    IDENTIFIER = 1,
    BOOLEAN_TRUE = 2,
    BOOLEAN_FALSE = 3,
    NUMBER = 4,
    CHARACTER = 5,
    STRING = 6,
    PAREN_START = 7,
    VECTOR_START = 8,
    BYTEVECTOR_START = 9,
    PAREN_END = 10,
    QUOTE = 11,
    BACKTICK = 12,
    COMMA = 13,
    COMMA_ATSIGN = 14,
    PERIOD = 15,
    DATUM_COMMENT = 16,
    COMMENT_START = 17,
    COMMENT_END = 18,
    DIRECTIVE = 19,
    END_OF_FILE = 0
  };

  Token::Type type;
  std::string str;
  LexInfo lex_info;

  Token(Token::Type type) :
      type(type),
      str("") {}

  Token(Token::Type type, const std::string& str) :
      type(type),
      str(str) {}

  Token(Token::Type type, const std::string& str, LexInfo lex_info) :
      type(type),
      str(str),
      lex_info(lex_info) {}

  bool operator==(const Token& other) {
    return (this->type == other.type &&
        this->str == other.str);
  }

  bool operator!=(const Token& other) {
    return !(operator==(other));
  }

  shaka::Token::Type get_type() const {
    return this->type;
  }

  std::string get_string() const {
    return this->str;
  }

  LexInfo get_lex_info() const {
    return this->lex_info;
  }

  friend bool operator==(const Token& lhs, const Token& rhs);
  friend bool operator!=(const Token& lhs, const Token& rhs);

};


std::ostream& operator<<(std::ostream& out, Token rhs);
bool operator==(const Token& lhs, const Token& rhs);
bool operator!=(const Token& lhs, const Token& rhs);

} // namespace shaka

#endif // SHAKA_LEXER_TOKEN_H
