#ifndef SHAKA_PARSER_RULES_RUL_PROC_CALL_H
#define SHAKA_PARSER_RULES_RUL_PROC_CALL_H

#include <cctype>

#include "parser/char_rules.h"

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
    std::string buffer;
    if(match_char<'('>(in, root, buffer)){
        while(!match_char<')'>(in, root, buffer)){
            
        }
    } else {
        return false;
    }
}


} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_PROC_CALL_H
