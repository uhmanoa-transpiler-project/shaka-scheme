#ifndef SHAKA_PARSER_RULES_RULE_EXPRESSION_H_
#define SHAKA_PARSER_RULES_RULE_EXPRESSION_H_

#include <cctype>
#include <exception>
#include <stack>

#include "parser/primitives.h"

#include "parser/Tokenizer.h"

namespace shaka {
namespace parser {
namespace rule {

// <expression> ::=
//      <identifier>         |
//      <proc call>          |
//      <lambda expr>        |
//      <conditional>        |
//      <assignment>         |
//      <derived expression> |
//      <macro use>          |
//      <macro block>        |
//      <includer>           |
template <typename T>
bool expression (
        InputStream&    in,
        NodePtr         root,
        T&              interm
);


} // rule
} // parser
} // shaka


#endif // SHAKA_PARSER_RULES_RULE_EXPRESSION_H_
