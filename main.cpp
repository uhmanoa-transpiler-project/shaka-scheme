#include <iostream>
#include <limits> // for std::numeric_limits for std::cin.ignore()
#include <vector>

#include "shaka_scheme/system/exceptions/BaseException.hpp"
#include "shaka_scheme/system/exceptions/TypeException.hpp"
#include "shaka_scheme/system/vm/HeapVirtualMachine.hpp"
#include "shaka_scheme/system/vm/compiler/Compiler.hpp"
#include "shaka_scheme/system/vm/strings.hpp"
#include "shaka_scheme/system/lexer/rules/rule_token.hpp"
#include "shaka_scheme/system/lexer/rules/init.hpp"
#include "shaka_scheme/system/parser/parser_definitions.hpp"

int main() {
  // Given: the lexer rules are initialized
  shaka::lexer::rules::init_lexer_rules();

  std::cout << "Welcome to Shaka Scheme!" << std::endl;

  bool done = false;
  //shaka::Token token(shaka::Token::Type::END_OF_FILE, "\0");
  //shaka::Tokenizer input(std::cin);
  //while (!done) {
  //  std::cout << "> " << std::flush;
  //  try {
  //    token = input.get();
  //    std::cout << token << std::endl;
  //    if (token.get_type() == shaka::Token::Type::DIRECTIVE) {
  //      if (token.get_string() == std::string("quit")) {
  //        done = true;
  //      }
  //    }
  //  } catch (shaka::BaseException e) {
  //    std::cerr << e.what() << std::endl;
  //    std::cin.clear();
  //    std::cin.ignore(std::numeric_limits<int>::max());
  //  }
  //}

  std::string buf;

  shaka::EnvPtr top_level = std::make_shared<shaka::Environment>(nullptr);

  shaka::Closure string_append(top_level, nullptr,
                               std::vector<shaka::Symbol>(0),
  std::make_shared<shaka::Callable>(shaka::string_append), nullptr, true);


  top_level->set_value(shaka::Symbol("string-append"), create_node
      (string_append));

  shaka::ValueRib vr;

  shaka::HeapVirtualMachine hvm(nullptr, nullptr, top_level, vr, nullptr);

  shaka::Compiler compiler;

  shaka::Symbol halt("halt");

  auto halt_instruction = shaka::core::list(create_node(halt));

  while (!done) {
    std::cout << "> " << std::flush;
    try {
      getline(std::cin, buf);
      shaka::parser::ParserInput input(buf);
      auto result = shaka::parser::parse_datum(input);
      shaka::Expression expr = result.it;
      //std::cout << *expr << std::endl;
      shaka::Expression compiled = compiler.compile(expr, halt_instruction);
      //std::cout << *compiled << std::endl;
      hvm.set_expression(compiled);
      do {
          hvm.evaluate_assembly_instruction();

      } while (shaka::core::car(hvm.get_expression())->get<shaka::Symbol>() !=
          shaka::Symbol("halt"));
      std::cout << *hvm.get_accumulator() << std::endl;
    } catch (shaka::InvalidInputException e) {
      std::cerr << e.what() << std::endl;
    } catch (shaka::TypeException *e) {
      std::cerr << e->what() << std::endl;
    }
    catch (std::runtime_error e) {
      std::cerr << e.what() << std::endl;
    }
  }

  std::cout << "Exiting..." << std::endl;
  return 0;
}