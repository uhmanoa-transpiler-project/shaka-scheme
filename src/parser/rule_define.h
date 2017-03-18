#ifndef SHAKA_PARSER_RULES_RUL_DEFINE_H
#define SHAKA_PARSER_RULES_RUL_DEFINE_H

#include <cctype>
#include <exception>
#include <functional>
#include <stack>

#include "Number.h"
#include "Symbol.h"
#include "Data.h"

#include "parser/primitives.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"

namespace shaka {
namespace parser {
namespace rule {

// Define using tokens
template <typename T>
bool define(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {

    std::stack<shaka::Token> tokens;

    try {
        // Check if it starts with a open parenthesis
        if(in.peek().type != shaka::Token::Type::PAREN_START) 
            throw std::runtime_error("No open parenthesis");

        tokens.push(in.get());
        interm += tokens.top().get_string();

        // Open parenthesis must be followed by 'define'
        if(in.peek().type != shaka::Token::Type::IDENTIFIER &&
           in.peek().get_string() != "define")
            throw std::runtime_error("No define keyword");

        tokens.push(in.get());
        interm += tokens.top().get_string();

        // Get identifier after 'define'
        if(in.peek().type != shaka::Token::Type::IDENTIFIER)
            throw std::runtime_error("No followup identifier");

        tokens.push(in.get());
        interm += tokens.top().get_string();

        // Get end expression
        if(in.peek().type != shaka::Token::Type::IDENTIFIER &&
           in.peek().type != shaka::Token::Type::NUMBER     &&
           in.peek().type != shaka::Token::Type::CHARACTER  &&
           in.peek().type != shaka::Token::Type::STRING     &&
           in.peek().type != shaka::Token::Type::BOOLEAN_TRUE &&
           in.peek().type != shaka::Token::Type::BOOLEAN_FALSE)
            throw std::runtime_error("No followup expression");

        tokens.push(in.get());
        interm += tokens.top().get_string();

        // Get end closing parenthesis
        if(in.peek().type != shaka::Token::Type::PAREN_END)
            throw std::runtime_error("No closing paren");

        tokens.push(in.get());
        interm += tokens.top().get_string();

        return true;


    // If define failed to parse, then put all tokens
    // back on the Tokenizer for use elsewhere
    } catch (std::runtime_error& e) {

        while(!tokens.empty()) {
            in.unget(tokens.top());
            tokens.pop();
        }
        return false;
    }
}

} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_PROC_CALL_H
