#include <gmock/gmock.h>

#include "shaka_scheme/system/parser/parser_definitions.hpp"
#include "shaka_scheme/system/vm/HeapVirtualMachine.hpp"
#include "shaka_scheme/system/parser/syntax_rules/macro_engine.hpp"

using namespace shaka::core;
using namespace shaka::macro;
using namespace shaka;


TEST(MacroContext, setup_vm) {
  const auto& c = create_node;
  NodePtr acc = create_node(Symbol("hi"));

  NodePtr expr0 =
      core::list(
          c(Symbol("constant")),
          c(PrimitiveFormMarker("set!")),
          core::list(
              c(Symbol("assign")),
              c(Symbol("set!")),
              core::list(c(Symbol("halt")))
          )
      );

  NodePtr expr =
      core::list(
          c(Symbol("constant")),
          c(PrimitiveFormMarker("lambda")),
          core::list(
              c(Symbol("assign")),
              c(Symbol("lambda")),
              expr0
          )
      );

  std::cout << *expr << std::endl;

  EnvPtr env = std::make_shared<Environment>(nullptr);
  std::deque<NodePtr> value_rib;
  std::shared_ptr<CallFrame> frame_ptr = std::make_shared<CallFrame>();

  HeapVirtualMachine hvm(acc, expr, env, value_rib, nullptr);

  hvm.evaluate_assembly_instruction();
  std::cout << *hvm.get_expression() << std::endl;
  hvm.evaluate_assembly_instruction();
  std::cout << *hvm.get_expression() << std::endl;
  hvm.evaluate_assembly_instruction();
  std::cout << *hvm.get_expression() << std::endl;
  hvm.evaluate_assembly_instruction();
  std::cout << *hvm.get_expression() << std::endl;

  for (auto it : hvm.get_environment()->get_bindings()) {
    std::cout << it.first << " :: " << *it.second << std::endl;
  }
}

/**
 * @brief Test: mock define expression
 */
TEST(MacroContext, other) {
  using namespace shaka::parser;
  using namespace shaka;
  // Given: an input string
  //std::string buf = "(lambda (x) (+ x z) (lambda (y) (- y a)) (lambda (q)
  // a))";
  //std::string buf = "(quote (lambda (x) (+ x x)))";
  std::string buf = "((lambda (x) (lambda (y) (define (hi x) y) (+ x y))) "
      "(lambda (x) (+ x x)))";

  // Given: a ParserInput loaded with the input string.
  parser::ParserInput input(buf);

  // Given: the results will end up in this results vector.
  auto result = parser::parse_datum(input);

  HeapVirtualMachine hvm(
      create_node(String("hello world")),
      core::list(create_node(Symbol("halt"))),
      std::make_shared<Environment>(nullptr),
      ValueRib(),
      nullptr
  );

  EnvPtr env = hvm.get_environment();

  env->set_value(Symbol("define"), create_node(PrimitiveFormMarker("define")));
  env->set_value(Symbol("set!"), create_node(PrimitiveFormMarker("set!")));
  env->set_value(Symbol("lambda"), create_node(PrimitiveFormMarker("lambda")));
  env->set_value(Symbol("quote"), create_node(PrimitiveFormMarker("quote")));
  env->set_value(Symbol("define-syntax"),
                 create_node(PrimitiveFormMarker("define-syntax")));
  env->set_value(Symbol("let-syntax"),
                 create_node(PrimitiveFormMarker("let-syntax")));
  env->set_value(Symbol("syntax-rules"),
                 create_node(PrimitiveFormMarker("syntax-rules")));

  ASSERT_EQ(PrimitiveFormMarker("define"),
            env->get_value(Symbol("define"))->get<PrimitiveFormMarker>());
  ASSERT_EQ(PrimitiveFormMarker("set!"),
            env->get_value(Symbol("set!"))->get<PrimitiveFormMarker>());
  ASSERT_EQ(PrimitiveFormMarker("lambda"),
            env->get_value(Symbol("lambda"))->get<PrimitiveFormMarker>());
  ASSERT_EQ(PrimitiveFormMarker("quote"),
            env->get_value(Symbol("quote"))->get<PrimitiveFormMarker>());
  ASSERT_EQ(PrimitiveFormMarker("define-syntax"),
            env->get_value(Symbol("define-syntax"))
                ->get<PrimitiveFormMarker>());
  ASSERT_EQ(PrimitiveFormMarker("let-syntax"),
            env->get_value(Symbol("let-syntax"))->get<PrimitiveFormMarker>());
  ASSERT_EQ(PrimitiveFormMarker("syntax-rules"),
            env->get_value(Symbol("syntax-rules"))->get<PrimitiveFormMarker>());

  // Given: an environment to hold bindings
  MacroContext context(hvm);
  std::cout << context << std::endl;
  std::cout << result << std::endl;

  if (!result.it) {
    std::cout << "result.it is not valid." << std::endl;
  }

  std::cout << *result.it << std::endl;

  traverse_tree(result.it, context);

  for (
    auto binding :
      context.identifier_bindings) {
    std::cout << "{" << binding.first << " | " << binding.second.scopes <<
              std::endl;
  }

// Given:
}

