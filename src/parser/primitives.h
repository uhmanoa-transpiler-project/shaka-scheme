#ifndef SHAKA_PARSER_PRIMITIVES_H
#define SHAKA_PARSER_PRIMITIVES_H

#include "DataNode.h"
#include "parser/Tokenizer.h"

namespace shaka {

namespace parser {

using InputStream = shaka::Tokenizer;
using NodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
using Node = shaka::DataNode<shaka::Data>;

/// @brief The general type signature of Rule procedures
///
/// Takes in the input stream, root node pointer, and
/// intermediate data node ptr.
///
/// The conventional variable names for each are, respectively:
/// - in
/// - root
/// - interm
///
/// Returns whether the rule matches or not.
template <typename T>
using Rule = std::function<
    bool(                   // Accept/reject of rule
        InputStream&,       // Input stream
        NodePtr,            // Root node
        T&                  // Intermediate data store variable
                            // - Treat it as "scratchwork"
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
