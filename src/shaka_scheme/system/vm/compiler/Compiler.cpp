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

    return list(create_node(instruction_data), input, next_instruction);
  }
  // (pair? input)
  else if (is_pair(input)) {
    Symbol expression_type = car(input)->get<Symbol>();

    // quote case
    // (list 'constant obj next)
    if(expression_type == Symbol("quote")){
      Symbol instruction("constant");
      Data instruction_data(instruction);

      return list(create_node(instruction_data), cdr(input), next_instruction);
    }
    // lambda case
    // (list ’close vars (compile body ’(return)) next)
    else if (expression_type == Symbol("lambda")) {
      Symbol instruction("close");
      Data instruction_data(instruction);

      Data return_op(Symbol("return"));

      NodePtr vars = car(cdr(input));
      NodePtr body = car(cdr(cdr(input)));

      return list(create_node(instruction_data),
                  vars,
                  compile(body,list(create_node(return_op))),
                  next_instruction);

    }
    // if (test then else) case
    else if (expression_type == Symbol("if")){
      Symbol instruction("test");
      Data instruction_data(instruction);

      NodePtr _test = car(cdr(input));
      NodePtr _then = car(cdr(cdr(input)));
      NodePtr _else = cdr(cdr(cdr(input)));

      Expression thenc = compile(_then, next_instruction);
      Expression elsec = compile(_else, next_instruction);

      return compile(_test, list(create_node(instruction_data), thenc, elsec));

    }
    // set! case
    else if (expression_type == Symbol("set!")){
      Symbol instruction("assign");
      Data instruction_data(instruction);

      NodePtr var = car(cdr(input));
      NodePtr x = car(cdr(cdr(input)));

      return compile(x, list(create_node(instruction_data), var, next_instruction));
    }
    // call/cc case
    else if (expression_type == Symbol("call/cc")) {
      Data argument_op(Symbol("argument"));
      Data conti_op(Symbol("conti"));
      Expression apply_op = create_node(Data(Symbol("apply")));

      Expression x = car(cdr(input));
      DataPair argument_compile(argument_op, *compile(x, apply_op));
      Expression c = list(create_node(conti_op), list(create_node
                                                     (argument_compile)));
      if (is_tail(next_instruction)) {
        return c;
      }
      else {
        Data frame_op(Symbol("frame"));
        return list(create_node(frame_op), next_instruction, c);
      }
    }
    // application
    else {
      Symbol apply_instruction("apply");
      Expression apply_op = create_node(Data(apply_instruction));

      NodePtr args = cdr(input);
      Expression c = compile(car(input), list(apply_op));

      while(true) {
        if (is_null_list(args)) {
          if(is_tail(next_instruction)) {
           return c;
          }
          else {
            Data frame_op(Symbol("frame"));

            // return (frame next c)
            return list(create_node(frame_op), next_instruction, c);
          }
        }
        Data argument_op(Symbol("argument"));
        DataPair argument_c(argument_op, *c);

        // (compile (car args) (argument c))
        c = compile(car(args), list(create_node(argument_op), c));
        args = cdr(args);
      }
    }
  }
  else {
    // (list 'constant x next)
    Symbol instruction("constant");
    Data instruction_data(instruction);

    // (constant x next)
    return list(create_node(instruction_data), input, next_instruction);
  }
}

bool Compiler::is_tail(Expression next) {
 return car(next)->get<Symbol>() == Symbol("return");
}

}
