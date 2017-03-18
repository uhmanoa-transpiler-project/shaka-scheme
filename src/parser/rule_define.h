#ifndef SHAKA_PARSER_RULES_RUL_DEFINE_H
#define SHAKA_PARSER_RULES_RUL_DEFINE_H

#include <cctype>
#include <functional>
#include <vector>

#include "Number.h"
#include "Symbol.h"

#include "parser/char_rules.h"
#include "parser/rule_number.h"

namespace shaka {
namespace parser {
namespace rule {

// BNF:
// <define> ::= (\s*define\s+<letter>+\s+<number>\s*)
template <typename T>
bool define(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    char c;

    using DataNode = shaka::DataNode<shaka::Data>;
    using NodeP = std::shared_ptr<shaka::DataNode<shaka::Data>>;

    /* Begin to parse if input begins with a '('.
     * It MUST begin with this, otherwise it cannot be define.
     */
    if(match_char<char, '('>(in, root, c)){
        std::string builder;
        NodeP topNode = std::make_shared<DataNode>(shaka::MetaTag::DEFINE);
        
        /* Ignore leading white space */
        while(space(in, root, c));
        /* Parse only enough to find the keyword 'define'. */
        for(int i = 0; i < 6; i++)      alpha(in, root, interm);
        if(interm != "define")          return false;
        /* Check for a space and ignore extra spaces */
        if(!space(in, root, interm))    return false;
        while(space(in, root, c));
        /* Define must be followed by a word */
        if(!alpha(in, topNode, builder))    return false;
        while(alpha(in, topNode, builder));
        NodeP symbolNode = std::make_shared<DataNode>(shaka::Symbol(builder));

        //NodePtr firstChild();
        /* Word must be followed by a space, ignore extras */
        if(!space(in, root, interm))    return false;
        while(space(in, root, c));
        /* Must be followed by an integer */
        if(!integer(in, root, interm))  return false;
        /* Ignore trailing whitespace */
        while(space(in, root, c));
        /* Must have matching closing ')'. */
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
