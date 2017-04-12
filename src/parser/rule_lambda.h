#ifndef SHAKA_PARSER_RULES_RULE_LAMBDA_H
#define SHAKA_PARSER_RULES_RULE_LAMBDA_H

#include <cctype>
#include <exception>
#include <stack>

#include "parser/primitives.h"

#include "Number.h"
#include "Symbol.h"

#include "parser/Tokenizer.h"

namespace shaka {
namespace parser {
namespace rule {

// <Lambda expression> ::= (lambda <Formals> <body>)
template <typename T>
bool lambda (
        InputStream&    in, 
        NodePtr         root, 
        T&              interm
);


// <formals> ::= (<identifer>*) | <identifier> | (<identifier>+ . <identifier>)
template <typename T>
bool formals(InputStream& in, NodePtr root, T& interm);

// <body> ::= <definition>* <sequence>
template <typename T>
bool body(InputStream& in, NodePtr root, T& interm);

        

} // rule
} // parser
} // shaka

#endif // SHAKA_PARSER_RULE_RULE_LAMBDA_H
