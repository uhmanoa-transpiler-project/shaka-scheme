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
    NodePtr lambdaNode; // Top node of lambda
    NodePtr argsNode;   // Node that all identifier arguments are passed to
    NodePtr bodyNode;   // Node which is a list of expressions in body

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
        // add lambda node as well as its argument and body nodes
        if(root != nullptr) {
            lambdaNode = root->push_child(shaka::Data{shaka::MetaTag::LAMBDA});
            argsNode   = lambdaNode->push_child(shaka::MetaTag::LIST);
            bodyNode   = lambdaNode->push_child(shaka::MetaTag::LIST);
        }


        // Function below parses in the <formals> sub rule
        // Pass in argsNode to populate with arguments from formals
        if( !formals(in, argsNode, interm) )
            throw std::runtime_error("LAMBDA: Failed to parse Formals");
        interm += " ";

        // function below parses in the <body> rule
        // Pass in bodyNode to get all expressions in body
        if( !body(in, bodyNode, interm) )
            throw std::runtime_error("LAMBDA: Failed to parse Body");

        // Parse in final ending close parenthesis
        if(in.peek().type != shaka::Token::Type::PAREN_END)
            throw std::runtime_error("LAMBDA: No required close parenthesis");

        tokens.push(in.get());
        interm += tokens.top().get_string();

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

        // Covers case of single identifier
        if(tokens.top().type == shaka::Token::Type::IDENTIFIER) {
            if(root != nullptr) {
                root->push_child(shaka::Symbol(tokens.top().get_string()));
            }
            return true;
        }

        // Next we can have either:
        // 1. <Identifier*>)
        // 3. <Identifier>+ . <Identifier>)
        
        // Base case, no arguments, '()'
        if(in.peek().type == shaka::Token::Type::PAREN_END) {
            tokens.push(in.get());
            interm += tokens.top().get_string();
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

            // Add each identifier to the argument list
            if(root != nullptr)
                root->push_child(shaka::Symbol(tokens.top().get_string()));
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

        if(tokens.top().type == shaka::Token::Type::PAREN_END)
            return true;

        // There was a '.', so add this '.' to the node list
        // TODO: Assess how to add this period, because it represents a list.
        //       Determine if this needs to become a new list node.
        if(root != nullptr)
            root->push_child(shaka::Symbol(tokens.top().get_string()));

        if(in.peek().type != shaka::Token::Type::IDENTIFIER)
            throw std::runtime_error("LAMBDA FORMALS: No final Identifier in Formal rule");

        tokens.push(in.get());
        interm += tokens.top().get_string();
        if(root != nullptr)
            root->push_child(shaka::Symbol(tokens.top().get_string()));

        if(in.peek().type != shaka::Token::Type::PAREN_END)
            throw std::runtime_error("LAMBDA FORMALS: No final end parenthesis in Formal rule");

        tokens.push(in.get());
        interm += tokens.top().get_string();

        return true;

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
        bool foundDefine = false;
        while( define(in, root, interm) ) {
            if(foundDefine) interm += " ";
            foundDefine = true;
        }


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
            if(foundDefine) interm += " ";
            interm += in.get().get_string();

            // Add expression to tree.
            // TODO: Replace this while loop with the actual expression
            //       function once it is finished
            if(root != nullptr) root->push_child(shaka::Symbol(tokens.top().get_string()));
        }

        if(!foundDefine && !foundExpression) 
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
