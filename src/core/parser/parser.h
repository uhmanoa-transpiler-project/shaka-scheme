#ifndef SHAKA_CORE_PARSER_PARSE_H_
#define SHAKA_CORE_PARSER_PARSE_H_

#include <stack>
#include "core/parser/primitives.h"

namespace shaka {
namespace parser {


template <typename T>
bool parse(
    InputStream&    in,
    NodePtr         node
) {

    // Parse in everything as one of the following:
    // 1. Symbol
    // 2. Number
    // 3. String
    // 4. Boolean
    //
    // Symbol : DataNode sNode(shaka::Symbol("symbol here"));
    // Number : DataNode nNode(shaka::Number(4563));
    // String : DataNode sNode(shaka::String("Hello world!"));
    // Boolean: DataNode bNode(shaka::Boolean(true));
    //
    // Node manipulation:
    //
    


}


} // parser
} // shaka

#endif // SHAKA_CORE_PARSER_PARSE_H_
