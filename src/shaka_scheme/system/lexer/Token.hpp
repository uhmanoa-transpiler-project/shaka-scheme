#ifndef SHAKA_LEXER_TOKEN_H
#define SHAKA_LEXER_TOKEN_H

#include "shaka_scheme/system/lexer/LexInfo.hpp"

#include <iostream>
#include <string>

namespace shaka {

struct Token {
public:

  std::string type;
  std::string str;
  LexInfo lex_info;

  Token(std::string type) :
      type(type),
      str("") {}

  Token(std::string type, const std::string& str) :
      type(type),
      str(str) {}

  Token(std::string type, const std::string& str, LexInfo lex_info) :
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

  std::string get_type() const {
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
