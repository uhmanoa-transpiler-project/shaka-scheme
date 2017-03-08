#ifndef SHAKA_PARSER_RULE_CHAR_RULES_H
#define SHAKA_PARSER_RULE_CHAR_RULES_H

#include <cctype>

#include "parser/primitives.h"

namespace shaka {
namespace parser {
namespace rule {


/// @brief Matches a digit character, and then appends it to
///        `interm`.
template <typename T>
bool match_paren(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if (in.peek() == '(' || in.peek() == ')') {
        interm += in.get();
        return true;        
    } else {
        return false;
    }
}

} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_CHAR_RULES_H
