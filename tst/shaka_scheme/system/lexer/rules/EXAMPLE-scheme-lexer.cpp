#include "shaka_scheme/system/lexer/rules/rule_token.hpp"
#include "shaka_scheme/system/lexer/rules/init.hpp"


#include <iostream>


int main() {
  using namespace shaka::lexer;
  shaka::lexer::rules::init_lexer_rules();
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
      skip_ws(lex);
      result = rules::scheme_lexer(lex);
      std::cout << "<< " << result << std::endl;
    } while (result.is_token());

  }
}


