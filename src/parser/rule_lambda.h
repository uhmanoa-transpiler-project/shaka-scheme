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

namespace shake {
namespace parser {
namespace rule {

template <typename T>
bool lambda (InputStream& in, NodePtr root, T& interm) {
    if(match_char<char, '('>(in, root, c)) {
        std::string builder;
        NodePtr topNode(shaka::MetaTag::LAMBDA);

        while(space(in, root, c));

        for(int i = 0; i < 6; i++)      alpha(in, root, interm);
        if(interm != "lambda")          return false;

        if(!space(in, root, interm))    return false;
        while(space(in, root, c));

        // formals(in, root, interm)
        // body(in, root, interm)

        while(space(in, root, c));
        if(match_char<char, ')'>(in, root, c)) return true;
        return false;
  }
     else { return false; }
}

// <formals> ::= (<identifer>*) | <identifier> | (<identifier>+ . <identifier)
bool formals(InputStream& in, NodePtr root, T& interm) {
  return false;
}

// <body> ::= <definition>* <sequence>
bool body(InputStream& in, NodePtr root, T& interm) {
  return false;
}

// <definition> ::= <command>*  <expression>
bool defintion(InputStream& in, NodePtr root, T& interm) {
  return false;
}

// <command> ::= <expression>
bool command(InputStream& in, NodePtr root, T& interm) {
  return false;
}

}}}

#endif // SHAKA_PARSER_RULE_RULE_LAMBDA_H
