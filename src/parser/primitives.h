#ifndef SHAKA_PARSER_PRIMITIVES_H
#define SHAKA_PARSER_PRIMITIVES_H

#include "DataNode.h"

namespace shaka {

namespace parser {

using InputStream = std::istream;
using NodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

/// @brief The general type signature of Rule procedures
///
/// Takes in the input stream, root node pointer, and
/// intermediate data node ptr.
///
/// Conventional names are:
/// - in
/// - root
/// - interm
///
/// Returns whether the rule matches or not.
using Rule = std::function<
    bool(                   // Accept/reject of rule
        InputStream&,      // Input stream
        NodePtr,            // Root node
        NodePtr             // Intermediate data node 
    )
>;

/// @brief The character type alias.
///
/// We may change this if we ever decide to transition to other
/// Unicode formats.
using Char = char;


} // namespace parser

} // namespace shaka



#endif // SHAKA_PARSER_PRIMITIVES_H
