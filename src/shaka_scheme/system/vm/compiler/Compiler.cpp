//
// Created by dylan on 10/4/17.
//

#include "shaka_scheme/system/vm/compiler/Compiler.hpp"

namespace shaka {
using namespace core;

Compiler::Compiler() {}

Compiler::~Compiler() {}

Expression Compiler::compile(Expression input, Expression
next_instruction) {
  // (symbol? input)
  if (is_symbol(input)) {
    Symbol instruction("refer");
    Data instruction_data(instruction);

    return list(create_node(instruction_data), input, next_instruction);
  }
    // (pair? input)
  else if (is_pair(input)) {
    Symbol expression_type;
    if (car(input)->get_type() == shaka::Data::Type::SYMBOL) {
      expression_type = car(input)->get<Symbol>();
    }

    // quote case
    if (expression_type == Symbol("quote")) {
      Symbol instruction("constant");
      Data instruction_data(instruction);

      return list(create_node(instruction_data), car(cdr(input)),
                  next_instruction);
    }
      // lambda case
    else if (expression_type == Symbol("lambda")) {
      Symbol instruction("close");
      Data instruction_data(instruction);
      Data halt_op(Symbol("return"));

      NodePtr vars = car(cdr(input));
      NodePtr body = cdr(cdr(input));
      return list(create_node(instruction), vars,
                  compile_lambda(body,list(create_node(halt_op))),
                  next_instruction);
    }
      // if (test then else) case
    else if (expression_type == Symbol("if")) {

      Symbol instruction("test");
      Data instruction_data(instruction);

      Expression test_expression = car(cdr(input));
      Expression then_expression = car(cdr(cdr(input)));
      Expression then_compiled = compile(then_expression, next_instruction);

      if (length(input) > 3) {
        Expression else_expression = car(cdr(cdr(cdr(input))));
        Expression else_compiled = compile(else_expression, next_instruction);

        return compile(test_expression, list(create_node(instruction_data),
                                             then_compiled, else_compiled));
      }

      return compile(test_expression, list(create_node(instruction_data),
                                           then_compiled));
    }
      // set! case
    else if (
        expression_type == Symbol("set!") ||
        expression_type == Symbol("define")) {
      Symbol instruction("assign");
      Data instruction_data(instruction);

      NodePtr var = car(cdr(input));
      NodePtr x = car(cdr(cdr(input)));

      return compile(x,list(create_node(instruction_data),
                            var,next_instruction));
    }
      // call/cc case
        else if (expression_type == Symbol("call/cc")) {
      Symbol conti_instruction("conti");
      Expression conti_op = create_node(Data(conti_instruction));

      Symbol argument_instruction("argument");
      Expression argument_op = create_node(Data(argument_instruction));

      Symbol apply_instruction("apply");
      Expression apply_op = create_node(Data(apply_instruction));

      Expression c = list(conti_op, list(argument_op,
                                         compile(car(cdr(input)),
                                                 list(apply_op))));
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

      while (true) {
        if (is_null_list(args)) {
          if (is_tail(next_instruction)) {
            return c;
          } else {
            Data frame_op(Symbol("frame"));
            return list(create_node(frame_op), next_instruction, c);
          }
        }
        Data argument_op(Symbol("argument"));
        c = compile(car(args), list(create_node(argument_op), c));
        args = cdr(args);
      }
    }
  } else {
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

Expression Compiler::compile_lambda(Expression body, Expression next) {
  // Check if body is single expression
  if (length(body) <= 1) {
    return compile(car(body), next);
  }
  return compile(car(body), compile_lambda(cdr(body), next));
}

}
