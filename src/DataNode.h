#ifndef SHAKA_DATANODE_H
#define SHAKA_DATANODE_H

#include <boost/variant.hpp>

#include "IDataNode.h"

namespace shaka {



/// @brief The central data structure for a Scheme object.
///
/// The Shaka Scheme data node implements the core data structure
/// for all objects by providing a sum (variant) type. To leverage
/// already existing code, `boost::variant` from the Boost C++ Library
/// has been adopted to handle that part of the internal data structure.
///
/// DataNode is a variant-type node that is meant to be used as a part
/// of a tree data structure. As all Scheme programs are in the form of
/// trees due to the expression-only nature of the grammar and semantics
/// of the language, it is easy to idealize the organization of data as a
/// tree.
///
/// As it is the core data class for the project, it is also the primary
/// interface for data exchange within the program, along with DataTree.



struct DataNode : public IDataNode {

    template <typename... Args>
    DataNode(Args... args) :
        data(std::forward<Args>(args)...) {}

    /// @brief Auxillary "type-tags" used to decide whether the
    /// contained type should have children, according to the sematnics
    /// of the Meta Tag.
    ///
    /// For example, an `ATOM` should have no children nodes, but
    /// a `LIST` should have links to its children as a vector of pointers.
    enum class MetaTag : int {
        
        LIST,
        PROCEDURE,
        IF,
        PAIR,
        VECTOR,
        BYTEVECTOR,
        NULL_LIST,
        ATOM,
        RECORD
    };

    /// @brief `boost::variant` is being re-aliased for the
    /// readability purposes of the project.
    using Data = 
    boost::variant<
        bool,
        int,
        std::string,
        MetaTag
    >;


    /// The key tag by which **Disjointness of Types** (R7RS, Sect. 3.2)
    /// will be implemented with and be kept updated with.
    MetaTag type_tag;

    /// The internal variant data type that will contain
    /// a reference to one of the contained data types.
    Data    data;
};

// #include <map>
// 
// struct Environment {
//     std::map<std::string, DataNode> symbol_table;
// };

} // namespace shaka

#endif // SHAKA_DATANODE_H
