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
  if (is_symbol(input)) {
    Symbol instruction("refer");
    Data instruction_data(instruction);

    DataPair next(*input, *list(create_node(*next_instruction)));
    DataPair assembly(instruction_data, next);

    return create_node(assembly);
  }
  // (pair? input)
  else if (is_pair(input)) {
    Symbol expression_type = car(input)->get<Symbol>();

    // quote case
    // (list 'constant obj next)
    if(expression_type == Symbol("quote")){
      Symbol instruction("constant");
      Data instruction_data(instruction);

      DataPair next(*cdr(input), *list(create_node(*next_instruction)));
      DataPair assembly(instruction_data, next);

      return create_node(assembly);
    }
    // lambda case
    // (list ’close vars (compile body ’(return)) next)
    else if (expression_type == Symbol("lambda")) {

    }
    // if (test then else) case
    else if (expression_type == Symbol("if")){

    }
    // set! case
    else if (expression_type == Symbol("set!")){

    }
    // call/cc case
    else if (expression_type == Symbol("call/cc")) {

    }
    else {
    }
  }
  else {
    // (list 'constant x next)
    Symbol instruction("constant");
    Data instruction_data(instruction);

    DataPair next(*input, *list(create_node(*next_instruction)));
    DataPair assembly(instruction_data, next);

    return create_node(assembly);
  }
}
}
