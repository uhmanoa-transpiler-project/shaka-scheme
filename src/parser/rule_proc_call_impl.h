#ifndef SHAKA_PARSER_RULES_RULE_PROC_CALL_IMPL_H
#define SHAKA_PARSER_RULES_RULE_PROC_CALL_IMPL_H


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

        // TODO: Write code to parse dakine proc_call

        return true;

    } catch (std::runtime_error& err) {

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
