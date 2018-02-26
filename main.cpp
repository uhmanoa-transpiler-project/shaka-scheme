#include <iostream>
#include <limits> // for std::numeric_limits for std::cin.ignore()
#include <vector>
#include <shaka_scheme/runtime/stdproc/numbers_arithmetic.hpp>

#include "shaka_scheme/system/exceptions/BaseException.hpp"
#include "shaka_scheme/system/exceptions/TypeException.hpp"
#include "shaka_scheme/system/vm/HeapVirtualMachine.hpp"
#include "shaka_scheme/system/vm/compiler/Compiler.hpp"
#include "shaka_scheme/system/vm/strings.hpp"
#include "shaka_scheme/system/lexer/rules/rule_token.hpp"
#include "shaka_scheme/system/lexer/rules/init.hpp"
#include "shaka_scheme/system/parser/parser_definitions.hpp"
#include "shaka_scheme/system/parser/syntax_rules/macro_engine.hpp"

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

  {
    using namespace shaka;

    top_level->set_value(Symbol("define"),
                         create_node(PrimitiveFormMarker("define")));
    top_level->set_value(
        Symbol("set!"),
        create_node(PrimitiveFormMarker("set!")));
    top_level->set_value(Symbol("lambda"),
                         create_node(PrimitiveFormMarker("lambda")));
    top_level->set_value(
        Symbol("quote"),
        create_node(PrimitiveFormMarker("quote")));
    top_level->set_value(Symbol("define-syntax"),
                         create_node(PrimitiveFormMarker("define-syntax")));
    top_level->set_value(Symbol("let-syntax"),
                         create_node(PrimitiveFormMarker("let-syntax")));
    top_level->set_value(Symbol("syntax-rules"),
                         create_node(PrimitiveFormMarker("syntax-rules")));
  }

  shaka::Closure string_append(
      top_level,
      nullptr,
      std::vector<shaka::Symbol>(0),
      std::make_shared<shaka::Callable>(shaka::string_append),
      nullptr,
      true);
  top_level->set_value(
      shaka::Symbol("string-append"),
      create_node(string_append));

  shaka::Closure add_numbers(
      top_level,
      nullptr,
      std::vector<shaka::Symbol>(0),
      std::make_shared<shaka::Callable>(shaka::stdproc::add),
      nullptr,
      true);
  top_level->set_value(
      shaka::Symbol("+"),
      create_node(add_numbers));

  shaka::Closure sub_numbers(
      top_level,
      nullptr,
      std::vector<shaka::Symbol>(0),
      std::make_shared<shaka::Callable>(shaka::stdproc::sub),
      nullptr,
      true);
  top_level->set_value(
      shaka::Symbol("-"),
      create_node(sub_numbers));

  shaka::Closure mul_numbers(
      top_level,
      nullptr,
      std::vector<shaka::Symbol>(0),
      std::make_shared<shaka::Callable>(shaka::stdproc::mul),
      nullptr,
      true);
  top_level->set_value(
      shaka::Symbol("*"),
      create_node(mul_numbers));

  shaka::Closure div_numbers(
      top_level,
      nullptr,
      std::vector<shaka::Symbol>(0),
      std::make_shared<shaka::Callable>(shaka::stdproc::div),
      nullptr,
      true);
  top_level->set_value(
      shaka::Symbol("/"),
      create_node(div_numbers));

    shaka::Closure remainder_numbers(
            top_level,
            nullptr,
            std::vector<shaka::Symbol>(0),
            std::make_shared<shaka::Callable>(shaka::stdproc::remainder),
            nullptr,
            true);
    top_level->set_value(
            shaka::Symbol("remainder"),
            create_node(remainder_numbers));

  shaka::Closure display_datum(
      top_level,
      nullptr,
      std::vector<shaka::Symbol>(0),
      std::make_shared<shaka::Callable>(shaka::stdproc::display),
      nullptr,
      true);
  top_level->set_value(
      shaka::Symbol("display"),
      create_node(display_datum));

  shaka::ValueRib vr;

  shaka::HeapVirtualMachine hvm(nullptr, nullptr, top_level, vr, nullptr);

  shaka::Compiler compiler;

  shaka::Symbol halt("halt");

  auto halt_instruction = shaka::core::list(create_node(halt));

  while (!done) {
    try {
      std::cout << "> " << std::flush;
      getline(std::cin, buf);
      shaka::parser::ParserInput input(buf);
      auto result = shaka::parser::parse_datum(input);
      //std::cout << "parsed datum" << std::endl;
      if (result.is_lexer_error()) {
        std::cout << "LexerError: " << result << std::endl;
        input.tokens.clear();
        input.lex.input.clear();
        break;
      } else if (result.is_parser_error()) {
        std::cout << "ParserError: " << result << std::endl;
        continue;
      } else if (result.is_incomplete()) {
        std::cout << "Incomplete: " << result << std::endl;
        continue;
      }
      shaka::Expression expr = result.it;
      shaka::macro::MacroContext macro_context(hvm);
      shaka::macro::run_macro_expansion(expr, macro_context);
      //std::cout << "macro expanded datum" << std::endl;
      //std::cout << *expr << std::endl;
      shaka::Expression compiled = compiler.compile(expr, halt_instruction);
      //std::cout << "compiled datum" << std::endl;
      //std::cout << *compiled << std::endl;
      hvm.set_expression(compiled);
      do {
        hvm.evaluate_assembly_instruction();
      } while (shaka::core::car(hvm.get_expression())->get<shaka::Symbol>() !=
          shaka::Symbol("halt"));
      std::cout << *hvm.get_accumulator() << std::endl;
    } catch (shaka::InvalidInputException e) {
      std::cerr << "InvalidInputException: " << e.what() << std::endl;
    } catch (shaka::TypeException e) {
      std::cerr << "TypeException: " << e.what() << std::endl;
    }
    catch (std::runtime_error e) {
      std::cerr << "RuntimeError: " << e.what() << std::endl;
      break;
    }
  }

  std::cout << "Exiting..." << std::endl;
  return 0;
}