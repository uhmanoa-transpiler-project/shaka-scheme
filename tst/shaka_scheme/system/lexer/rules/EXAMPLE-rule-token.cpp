#include "shaka_scheme/system/lexer/rules/rule_token.hpp"


#include <iostream>


int main() {
  using namespace shaka::lexer;

  LexResult result = Incomplete("lol", LexInfo());
  LexerInput lex(std::string(), "test");
  std::string buf;

  auto skip_ws = *make_class([](char c) {
    return std::isspace(c);
  }, "whitespace");

  while (!result.is_error()) {
    if (result.is_incomplete()) {
      std::cout << ">> " << std::flush;
      std::getline(std::cin, buf, '\n');
      lex.append_input(buf + "\n");
    }
    do  {
      result = (skip_ws + rules::token)(lex);
      std::cout << "<< " << result << std::endl;
    } while (result.is_token());

  }
}


