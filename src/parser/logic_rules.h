#ifndef SHAKA_PARSER_RULE_LOGIC_RULES_H
#define SHAKA_PARSER_RULE_LOGIC_RULES_H

#include <vector>
#include <functional>
#include <cctype>

#include "parser/primitives.h"

namespace shaka {
namespace parser {
namespace rule {

template <typename T>
bool rules_or(
        InputStream&    in,
        NodePtr         root,
        T&              interm,
        std::vector<std::function<bool(InputStream&, NodePtr, T&)>> rules
){
    for(auto f : rules){
        if(f(in, root, interm)){
            return true;
        }
    }
    return false;
}


} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_LOGIC_RULES_H
