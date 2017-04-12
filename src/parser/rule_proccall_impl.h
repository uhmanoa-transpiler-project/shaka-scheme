#ifndef SHAKA_PARSER_RULES_RULE_PROCCALL_IMPL_H
#define SHAKA_PARSER_RULES_RULE_PROCCALL_IMPL_H


#include "parser/rule_proccall.h"
#include "parser/rule_quote.h"

// BNF:
// <procedure call> := (<operator> <operand>*)
// <operator>       := <expression>
// <operand>        := <expression>
//
// <expression> := <variable> | quote<datum> | '<datum> |
//                 <procedure call> | lambda<formals> <body> |
//                 if <test> <consequent> <alternative> |
//                 if <test> <consequent> | set! <variable> <expression> |
//                 derived expressions
template <typename T>
bool proc_call(InputStream& in, NodePtr root, T& interm) {
  std::stack<shaka::Token> tokens;

  try {
    // Must start with open parenthesis
    if(in.peek().type != shaka::Token::Type::PAREN_START)
      throw std::runtime_error("No open parenthesis");

    tokens.push(in.get());
    interm += tokens.top().get_string();

    return true;
  }
  catch(std::runtime_error& e) {
    while(!tokens.empty()) {
      in.unget(tokens.top());
      tokens.pop();
    }
    return false;
  }
}

template <typename T>
bool expr(InputStream& in, NodePtr root, T& interm) {
  std::stack<shaka::Token> tokens;
  return true;
}

#endif // SHAKA_PARSER_RULE_RULE_PROC_CALL_H
