#ifndef SHAKA_PARSER_RULES_RUL_DEFINE_H
#define SHAKA_PARSER_RULES_RUL_DEFINE_H

#include <cctype>
#include <functional>
#include <vector>

#include "parser/char_rules.h"
#include "parser/rule_number.h"

namespace shaka {
namespace parser {
namespace rule {

// BNF:
// <define> ::= (define <letter>+ <number>)
template <typename T>
bool define(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    char c;

    if(match_char<char, '('>(in, root, c)){

        while(space(in, root, c));
        for(int i = 0; i < 6; i++)      alpha(in, root, interm);
        if(interm != "define")          return false;
        if(!space(in, root, interm))    return false;
        while(space(in, root, c));
        if(!alpha(in, root, interm))    return false;
        while(alpha(in, root, interm));
        if(!space(in, root, interm))    return false;
        while(space(in, root, c));
        if(!integer(in, root, interm))  return false;
        while(space(in, root, c));
        if(match_char<char, ')'>(in, root, c)) return true;
        return false;
    } else {
        return false;
    }
}

} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_PROC_CALL_H
