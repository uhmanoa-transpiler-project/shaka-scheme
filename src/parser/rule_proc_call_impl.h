#ifndef SHAKA_PARSER_RULES_RULE_PROC_CALL_IMPL_H
#define SHAKA_PARSER_RULES_RULE_PROC_CALL_IMPL_H

#include <iostream> // debugging, remove later
#include <exception>
#include <stack>
#include <string>

#include "parser/rule_proc_call.h"

#include "parser/primitives.h"
#include "parser/Token.h"
#include "parser/Tokenizer.h"

namespace shaka {
namespace parser {
namespace rule {

// BNF:
// <procedure call> := (<operator> <operand>*)
// <operator>       := <expression>
// <operand>        := <expression>
//
// <expression> := <variable> | quote<datum> | '<datum> |
//                 <procedure call> | lambda<formals> <body> |
//                 if <test> <consequent> <alternative> |
//                 if <test> <consequent> | set! <variable> <expression> |
//                 derived expressions
template <typename T>
bool proc_call(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {

    std::stack<shaka::Token> tokens;
    NodePtr pcNode;

    try {

        // Must start with open parenthesis
        if( in.peek() != shaka::Token::Type::PAREN_START )
            throw std::runtime_error("No open parenthesis");

        tokens.push( in.get() );
        interm += tokens.top().get_string();

        // Get an identifier
        if( in.peek() != shaka::Token::Type::IDENTIFIER )
            throw std::runtime_error("No follow up identifier");

        tokens.push( in.get() );
        interm += tokens.top().get_string();

        ///////////////////////
        //    TEMP FOR NOW   //
        ///////////////////////

        if( in.peek() != shaka::Token::Type::NUMBER )
            throw std::runtime_error("No follow up number");

        tokens.push( in.get() );
        interm += " " + tokens.top().get_string();

        if( in.peek() != shaka::Token::Type::NUMBER )
            throw std::runtime_error("No follow up number");
           
        tokens.push( in.get() );
        interm += " " + tokens.top().get_string();

        if( in.peek() != shaka::Token::Type::PAREN_END ) 
            throw std::runtime_error("No follow up number");

        tokens.push( in.get() );
        interm += " " + tokens.top().get_string();

        //////////////////////
        //     END TEMP     //
        //////////////////////

        return true;

    } catch (std::runtime_error& err) {

        std::cout << err.what() << std::endl;

        // Put all used tokens back into stream
        while( !tokens.empty() ) {
            in.unget( tokens.top() );
            tokens.pop();
        }

        // delete pcNode and all children
        if( pcNode != nullptr ) {
            std::size_t size = pcNode->get_num_children();
            for(std::size_t i = 0; i < size; ++i) {
                pcNode->remove_child(i);
            }
        }

        return false;
    }
}

} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_PROC_CALL_IMPL_H
