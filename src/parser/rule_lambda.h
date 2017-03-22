#ifndef SHAKA_PARSER_RULES_RULE_LAMBDA_H
#define SHAKA_PARSER_RULES_RULE_LAMBDA_H

#include <cctype>
#include <functional>
#include <vector>

#include "Number.h"
#include "Symbol.h"

#include "parser/char_rules.h"
#include "parser/rule_number.h"
#include "parser/Tokenizer.h"

namespace shaka {
namespace parser {
namespace rule {

template <typename T>
bool lambda (InputStream& in, NodePtr root, T& interm) {
    if(match_char<char, '('>(in, root, interm)) {
        std::string builder;
        NodePtr topNode(shaka::MetaTag::LAMBDA);

        while(space(in, root,interm));

        for(int i = 0; i < 6; i++)      alpha(in, root, interm);
        if(interm != "lambda")          return false;

        if(!space(in, root, interm))    return false;
        while(space(in, root, interm));

        if (!formals(in, root, interm)) return false;
        // body(in, root, interm)

        while(space(in, root, interm));
        if(match_char<char, ')'>(in, root, interm)) return true;
        return false;
  }
     else { return false; }
}

// <formals> ::= (<identifer>*) | <identifier> | (<identifier>+ . <identifier>)
template <typename T>
bool formals(InputStream& in, NodePtr root, T& interm) {
  if (match_char<char, '('>(in, root, interm)) {
    while (true) {
      while(space(in, root, interm));
      shaka::Tokenizer tokenizer(in);
      if (in.peek() == ')') break;
      else if (tokenizer.parse_string().get_type() != Token::Type::IDENTIFIER) {
        return false;
      }
    }
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
  // expect definition
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
