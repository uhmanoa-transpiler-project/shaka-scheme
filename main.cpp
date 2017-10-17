#include <iostream>

#include "shaka_scheme/system/exceptions/BaseException.hpp"
#include "shaka_scheme/system/lexer/Tokenizer.hpp"

int main() {
  std::cout << "Welcome to Shaka Scheme!" << std::endl;

  bool done = false;
  shaka::Token token(shaka::Token::Type::END_OF_FILE, "\0");
  shaka::Tokenizer input(std::cin);
  while (!done) {
    std::cout << "> " << std::flush;
    try {
      token = input.get();
      std::cout << token << std::endl;
      if (token.get_type() == shaka::Token::Type::DIRECTIVE) {
        if (token.get_string() == std::string("quit")) {
          done = true;
        }
      }
    } catch (shaka::BaseException e) {
      std::cerr << e.what() << std::endl;
      std::cin.clear();
      std::cin.ignore(INT_MAX);
    }
  }

  std::cout << "Exiting..." << std::endl;
  return 0;
}