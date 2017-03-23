#ifndef SHAKA_PARSER_RULES_IDENTIFIER_DEFINE_H
#define SHAKA_PARSER_RULES_IDENTIFIER_DEFINE_H

#include <cctype>
#include <functional>
#include <vector>

#include "parser/primitives.h"
#include "parser/char_rules.h"
#include "parser/logic_rules.h"

namespace shaka {
namespace parser {
namespace rule {

// BNF for Peculiar Identifier
// Official:
// <peculiar identifier> -> 
//
// <explicit sign> | 
// <explicit sign> <sign subsequent> <subsequent>* |
// <explicit sign> . <dot subsequent> <subsequent>* |
// . <dot subsequent> <subsequent>*
template <typename T>
bool peculiar_identifier(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {

    // TODO: Is a . a '.' or anything . ?
    if (in.peek() == '+' ||
        in.peek() == '-' ||) {
        
        // Guarenteed to be a pecul. ident., need to check 
        // further variations
        interm += in.get(); 

        if ( sign_subsequent<T>(in, root, interm) ) {
            while( subsequent<T>(in, root, interm) );
            return true;

        } else if ( dot_subsequent<T>(in, root, interm) ) {
            while( subsequent<T>(in, root, interm) );
            return true;
        }



    } else if (in.peek() == '.') {
        // must be followed by dot subsequent, and 0 or more subsequent
        interm += in.get();

        if ( dot_subsequent<T>(in, root, interm) ) {
            while ( subsequent<T>(in, root, interm) );
            return true;
        }
    }

    return false;
}

} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_RULE_PROC_CALL_H
