#ifndef SHAKA_PARSER_RULES_RULE_PROCCALL_IMPL_H
#define SHAKA_PARSER_RULES_RULE_PROCCALL_IMPL_H

#include <cctype>
#include <exception>
#include <functional>
#include <stack>
#include <string>
#include <vector>

#include "parser/primitives.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"

#include "parser/rule_proccall.h"
#include "parser/rule_expression_impl.h"

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
  NodePtr procNode;

  try {
    // Must start with open parenthesis
    if(in.peek().type != shaka::Token::Type::PAREN_START)
      throw std::runtime_error("No open parenthesis");

    tokens.push(in.get());
    interm += tokens.top().get_string();
    if (root != nullptr)
      procNode = root->push_child(shaka::Data{shaka::MetaTag::PROC_CALL});

    if (in.peek().type != shaka::Token::Type::IDENTIFIER)
      throw std::runtime_error("BRUH WTF");

    tokens.push(in.get());
    interm += tokens.top().get_string();

    if (procNode != nullptr)
      procNode->push_child(shaka::Symbol(tokens.top().get_string()));

    NodePtr listNode = procNode->push_child(shaka::Data{shaka::MetaTag::LIST});

    while (true) {
      if (!expression(in, listNode, ptr)) {
        break;
      }
    }

    if(in.peek().type != shaka::Token::Type::PAREN_END)
      throw std::runtime_error("No closing parenthesis");

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

#endif // SHAKA_PARSER_RULES_RULE_PROCCALL_IMPL_H
