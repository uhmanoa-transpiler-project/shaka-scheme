//
// Created by dylan on 10/4/17.
//

#include "shaka_scheme/system/vm/compiler/Compiler.hpp"

namespace shaka {
using namespace core;

Compiler::Compiler() {}

Compiler::~Compiler() {}

Expression Compiler::compile(Expression input, Expression next_instruction) {
  // (symbol? input)
  // (list 'refer x next)
  if (is_symbol(car(input))) {
    Symbol instruction("refer");
    Data instruction_data(instruction);

    DataPair next(*car(input), *list(create_node(*next_instruction)));
    DataPair assembly(instruction_data, next);
    Expression expression = create_node(assembly);

    return expression;
  }
  // (pair? input)
  else if (is_pair(input)) {
    // (list 'constant obj next)
  }
  else {
    // (list 'constant x next)
  }
}

//void Compiler::compile_step(Expression input, Expression output) {
//  if (core::is_symbol(core::car(input))) {
//   // append(output, input);
//  }
//}

}
