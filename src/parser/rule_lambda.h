#ifndef SHAKA_PARSER_RULES_RULE_LAMBDA_H
#define SHAKA_PARSER_RULES_RULE_LAMBDA_H

#include <cctype>
#include <exception>
#include <functional>
#include <vector>
#include <stack>

#include "Number.h"
#include "Symbol.h"

#include "parser/char_rules.h"
#include "parser/rule_number.h"
#include "parser/Tokenizer.h"

namespace shaka {
namespace parser {
namespace rule {

// <Lambda expression> ::= (lambda <Formals> <body>)
// 
template <typename T>
bool lambda (
        InputStream&    in, 
        NodePtr         root, 
        T&              interm
) {

    std::stack<shaka::Token> tokens;
    NodePtr lambdaNode;

    try {

        // Must start with open parenthesis
        if(in.peek().type != shaka::Token::Type::PAREN_START)
            throw std::runtime_error("No required open parenthesis");

        tokens.push(in.get());
        interm += tokens.top().get_string();

        // Parenthesis must be followed by lambda keyword
        if(in.peek().type != shaka::Token::Type::IDENTIFIER &&
           in.peek().get_string != "lambda")
            throw std::runtime_error("No Lambda keyword");

        tokens.push(in.get());
        interm += tokens.top().get_string();
        // add lambda node
        if(root != nullptr)
            lambdaNode = root->push_child(shaka::Data{shaka::MetaTag::LAMBDA});

        // ADD FORMALS CODE BELOW
        // Need to call function

        //////////////////////////

    } catch(std::runtime_error& e) {

        while(!tokens.empty()) {
            in.unget(tokens.top());
            tokens.pop();
        }

        // delete lambdaNode and children
        if(lambdaNode != nullptr) {

            std::size_t size = lambdaNode->get_num_children();
            for(std::size_t i = 0; i < size; ++i) {
                lambdaNode->remove_child(i);
            }
        }
        return false;
    }
}

// <formals> ::= (<identifer>*) | <identifier> | (<identifier>+ . <identifier>)
template <typename T>
bool formals(InputStream& in, NodePtr root, T& interm) {
  if (match_char<char, '('>(in, root, interm)) {
    while (true) {
      while(space(in, root, interm));
      shaka::Tokenizer tokenizer(in);
      if (in.peek() == ')') break;
      else if (tokenizer.parse_string().get_type() == Token::Type::IDENTIFIER) {
        while (true) {
          while(space(in, root, interm));
          if (tokenizer.parse_string().get_type() != Token::Type::IDENTIFIER) break;
        }
        if (in.peek() == '.') {
          while(space(in, root, interm));
          if (tokenizer.parse_string().get_type() != Token::Type::IDENTIFIER) return false;
        }
      }
      else if (tokenizer.parse_string().get_type() != Token::Type::IDENTIFIER) {
        return false;
      }
    }
    while(space(in, root, interm));
    if (match_char<char, ')'>(in, root, interm)) return true;
    return false;
  }
  else {
    shaka::Tokenizer tokenizer(in);
    if (tokenizer.parse_string().get_type() == Token::Type::IDENTIFIER) {
      return true;
    }
  }
  return false;
}

// <body> ::= <definition>* <sequence>
template <typename T>
bool body(InputStream& in, NodePtr root, T& interm) {
  if (definition(in, root, interm)) {
    while (definition(in, root, interm));
  }
  // expect sequence
  return false;
}

// <definition> ::= <command>*  <expression>
template <typename T>
bool defintion(InputStream& in, NodePtr root, T& interm) {
  // expect command
  // expect expression
  return false;
}

// <command> ::= <expression>
template <typename T>
bool command(InputStream& in, NodePtr root, T& interm) {
  // expect expression
  return false;
}

}
}
}

#endif // SHAKA_PARSER_RULE_RULE_LAMBDA_H
