#ifndef SHAKA_PARSER_RULES_RULE_DEFINE_H
#define SHAKA_PARSER_RULES_RULE_DEFINE_H

#include "parser/primitives.h"

namespace shaka {
namespace parser {
namespace rule {

// Define using tokens
template <typename T>
bool define(
    InputStream&    in,
    NodePtr         root, // shared ptr to IDataNode<Data>
    T&              interm
);

} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_DEFINE_H
