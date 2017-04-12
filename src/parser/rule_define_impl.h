#ifndef SHAKA_PARSER_RULES_RULE_DEFINE_IMPL_H
#define SHAKA_PARSER_RULES_RULE_DEFINE_IMPL_H

#include <cctype>
#include <exception>
#include <functional>
#include <stack>
#include <string>

#include "rule_define.h"

#include "Number.h"
#include "Symbol.h"
#include "Data.h"
#include "IDataNode.h"

#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Define.h"
#include "Procedure.h"
#include "Eval_Expression.h"
#include "Eval_Define_impl.h"
#include "Eval_Variable_impl.h"
#include "Eval_PrintTree.h"

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
    NodePtr defNode;
    shaka::Data tag = shaka::MetaTag::DEFINE;

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
        interm += " ";
        // add NODE
        if(root != nullptr)
            defNode = root->push_child(shaka::Data{shaka::MetaTag::DEFINE});

        // Get identifier after 'define'
        if(in.peek().type != shaka::Token::Type::IDENTIFIER)
            throw std::runtime_error("No followup identifier");

        tokens.push(in.get());
        interm += tokens.top().get_string();
        interm += " ";
        // Add Symbol for identifier to tree
        if(defNode != nullptr)
            defNode->push_child(shaka::Symbol(tokens.top().get_string()));

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
        if(defNode != nullptr) {

            std::size_t size = defNode->get_num_children();
            for(std::size_t i = 0; i < size; ++i) {
                defNode->remove_child(i);
            }
        }
        
        return false;
    }
}


} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_DEFINE_IMPL_H
