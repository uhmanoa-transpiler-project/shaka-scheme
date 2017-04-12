#ifndef SHAKA_PARSER_RULES_RULE_EXPRESSION_IMPL_H_
#define SHAKA_PARSER_RULES_RULE_EXPRESSION_IMPL_H_

#include <cctype>
#include <exception>
#include <stack>

#include "parser/primitives.h"

#include "parser/rule_expression.h"
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
) {

    std::stack<shaka::Token> tokens;

    try {

        // First, I want to check for any rules that may be recursive
        // or that may include any of the smaller rules such as literal
        if(in.peek().type == shaka::Token::Type::PAREN_START)


    } catch(std::runtime_error& e) {

        return false;
    }
}


} // rule
} // parser
} // shaka


#endif // SHAKA_PARSER_RULES_RULE_EXPRESSION_IMPL_H_
