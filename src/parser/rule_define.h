#ifndef SHAKA_PARSER_RULES_RUL_DEFINE_H
#define SHAKA_PARSER_RULES_RUL_DEFINE_H

#include <cctype>
#include <exception>
#include <functional>
#include <stack>
#include <string>

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
    NodePtr         root, // shared ptr to IDataNode<Data>
    T&              interm
) {

    std::stack<shaka::Token> tokens;
    std::shared_ptr<Node> defNode;

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
        // add NODE
        //if(root != nullptr) 
        //    defNode = root->push_child(shaka::MetaTag::DEFINE);

        // Get identifier after 'define'
        if(in.peek().type != shaka::Token::Type::IDENTIFIER)
            throw std::runtime_error("No followup identifier");

        tokens.push(in.get());
        interm += tokens.top().get_string();
        // Add Symbol for identifier to tree
        //if(defNode != nullptr)
        //    defNode->push_child(shaka::Symbol(tokens.top().get_string));

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
        /*
        switch(tokens.top().type) {

            case shaka::Token::Type::NUMBER:
                // Push Number under define node
                if(defNode != nullptr) {
                    defNode->push_child(
                        shaka::Number( 
                            std::stod( tokens.top().get_string() )
                        )
                    );
                }
                break;
            case shaka::Token::Type::IDENTIFIER:
            case shaka::Token::Type::CHARACTER:
            case shaka::Token::Type::STRING:
            case shaka::Token::Type::BOOLEAN_TRUE:
            case shaka::Token::Type::BOOLEAN_FALSE:
            default:
                // push symbol under define node
                if(defNode != nullptr) {
                    defNode->push_child(
                            shaka::Symbol( tokens.top().get_string() )
                            );
                }
                break;
        }
        */
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
        // delete defNode and children
        //if(defNode != nullptr) {
            // TODO: Execute Order 66
            // AKA Delete all children of defNode
            //     and delete defNode
        //}
        return false;
    }
}

} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_PROC_CALL_H
