#ifndef SHAKA_PARSER_RULES_RULE_LAMBDA_IMPL_H
#define SHAKA_PARSER_RULES_RULE_LAMBDA_IMPL_H

#include <cctype>
#include <exception>
#include <stack>

#include "parser/primitives.h"

#include "parser/rule_lambda.h"
#include "parser/rule_define_impl.h"
#include "parser/Tokenizer.h"

#include "Number.h"
#include "Symbol.h"

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
            throw std::runtime_error("LAMBDA: No required open parenthesis");

        tokens.push(in.get());
        interm += tokens.top().get_string();

        // Parenthesis must be followed by lambda keyword
        if(in.peek().get_string() != "lambda")
            throw std::runtime_error("LAMBDA: No Lambda keyword");

        tokens.push(in.get());
        interm += tokens.top().get_string();
        interm += " ";
        // add lambda node
        if(root != nullptr)
            lambdaNode = root->push_child(shaka::Data{shaka::MetaTag::LAMBDA});


        // Function below parses in the <formals> sub rule
        if( !formals(in, root, interm) ) 
            throw std::runtime_error("LAMBDA: Failed to parse Formals");
        interm += " ";

        // function below parses in the <body> rule
        if( !body(in, root, interm) )
            throw std::runtime_error("LAMBDA: Failed to parse Body");

        // Parse in final ending close parenthesis
        if(in.peek().type != shaka::Token::Type::PAREN_END)
            throw std::runtime_error("LAMBDA: No required close parenthesis");

        tokens.push(in.get());
        interm += tokens.top().get_string();
        // TODO: TREE

        // Parsed in everything successfully
        return true;

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

    std::stack<shaka::Token> tokens;

    try {

        // Check for '(' or identifier
        if(in.peek().type != shaka::Token::Type::PAREN_START &&
           in.peek().type != shaka::Token::Type::IDENTIFIER)
            throw std::runtime_error("LAMBDA FORMALS: No formal following lambda keyword");

        tokens.push(in.get());
        interm += tokens.top().get_string();

        // TODO: Tree insertions

        // Covers case of single identifier
        if(tokens.top().type == shaka::Token::Type::IDENTIFIER)
            return true;

        // Next we can have either:
        // 1. <Identifier*>)
        // 3. <Identifier>+ . <Identifier>)
        
        // Base case, no arguments, '()'
        if(in.peek().type == shaka::Token::Type::PAREN_END) {
            tokens.push(in.get());
            interm += tokens.top().get_string();
            // TODO: FILL TREE
            return true;
        }
        // Next up:
        // 1. <Identifier>+)
        // 2. <Identifier>+ . <Identifier>)

        // Parse all next identifiers
        bool foundIdentifier = false;
        while(in.peek().type == shaka::Token::Type::IDENTIFIER) {

            if(foundIdentifier) interm += " "; // so interm is well formatted
            tokens.push(in.get());
            interm += tokens.top().get_string();
            foundIdentifier = true;
            // TODO: add nodes to tree

        }
        if(!foundIdentifier) 
            throw std::runtime_error("LAMBDA FORMALS: No followup identifier in ()");

        // Check for the final ')' or the .
        if(in.peek().type != shaka::Token::Type::PAREN_END &&
           in.peek().type != shaka::Token::Type::PERIOD)
            throw std::runtime_error("LAMBDA FORMALS: No closing parenthesis or . in Formals");

        // Parse in ')' or '.'
        tokens.push(in.get());
        interm += tokens.top().get_string();
        // TODO: Insert to tree

        if(tokens.top().type == shaka::Token::Type::PAREN_END)
            return true;

        if(in.peek().type != shaka::Token::Type::IDENTIFIER)
            throw std::runtime_error("LAMBDA FORMALS: No final Identifier in Formal rule");

        tokens.push(in.get());
        interm += tokens.top().get_string();
        // TODO: TREE

        if(in.peek().type != shaka::Token::Type::PAREN_END)
            throw std::runtime_error("LAMBDA FORMALS: No final end parenthesis in Formal rule");

        tokens.push(in.get());
        interm += tokens.top().get_string();
        // TODO: TREE

    } catch(std::runtime_error& e) {

        while(!tokens.empty()) {
            in.unget(tokens.top());
            tokens.pop();
        }
        // TODO: Delete tree
    }
    return false;
}

// <body>          ::= <definition>* <sequence>
// <sequence>      ::= <command>* <expression>
// <body_sequence> ::= <<definition>* <expression>+
template <typename T>
bool body(InputStream& in, NodePtr root, T& interm) {

    try {
        // Calls the define rule each time a valid define is found
        // Parses 0 or more definitions
        // NOTE: THIS LOSES TOKENS
        while( define(in, root, interm) ) interm += " ";


        // TODO: FINISH EXPRESSION
        // NOTE: THIS LOSES TOKENS
        bool foundExpression = false;
        while(in.peek().type == shaka::Token::Type::IDENTIFIER   || 
              in.peek().type == shaka::Token::Type::NUMBER       || 
              in.peek().type == shaka::Token::Type::CHARACTER    || 
              in.peek().type == shaka::Token::Type::STRING       || 
              in.peek().type == shaka::Token::Type::BOOLEAN_TRUE ||
              in.peek().type == shaka::Token::Type::BOOLEAN_FALSE) 
        {
            foundExpression = true; 
            interm += in.get().get_string();
        }

        if(!foundExpression) 
            throw std::runtime_error("LAMBDA BODY: Failed to parse expression");
        else return true;

    } catch(std::runtime_error& e) {
        return false;
    }
}


} // rule
} // parser
} // shaka

#endif // SHAKA_PARSER_RULE_RULE_LAMBDA_IMPL_H
