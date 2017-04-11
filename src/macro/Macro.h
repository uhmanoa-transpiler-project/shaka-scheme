#ifndef SHAKA_MACRO_MACRO_H
#define SHAKA_MACRO_MACRO_H

#include <vector>
#include <memory>
#include <utility>

#include "DataNode.h"
#include "Procedure_impl.h"
#include "Eval_PrintTree.h"

namespace shaka {
namespace macro {

using INodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

class Pattern {
public:

    using Node = shaka::DataNode<shaka::Data>;

    /// @brief Should get the root of a tree that describes
    ///        the pattern to match to.
    ///
    ///        The tree will begin with a root node that is
    ///        a procedure call, as required by R7RS macros.
    ///        
    ///        Then, it will contain additional children
    ///        under its arguments root node of these possible types:
    ///        - List
    ///        - Identifiers
    ///        - Constants
    ///        - Ellipses
    ///
    ///        The tree must contain no other types of nodes.
    ///        To achieve this, `define-syntax` will have a 
    ///        special parsing rule delegated to it when parsing
    ///        as well as a unique evaluation rule and immutable
    ///        symbol assignment in the global environment.
    Pattern (INodePtr root, shaka::Symbol elipsis = {"..."}) :
        root(root),
        elipsis(elipsis) {}

    /// @todo Fix matches.
    /// @brief Will determine whether an evaluation tree root
    ///        conforms to the pattern as held in the tree.
    bool matches (INodePtr other_root) {
        if (other_root == nullptr) { return false; }
        else if (shaka::get<shaka::MetaTag>(*other_root->get_data()) == shaka::MetaTag::PROC_CALL) {
            return matches_recursive(this->root, other_root->get_child(1));
        }
    }

private:
    
    bool matches_recursive(INodePtr curr_node, INodePtr other_node) {
        std::cout << "@Pattern.matches: "
                  << curr_node->get_data()->type().name()
                  << " : " << other_node->get_data()->type().name() << std::endl;
        // If the current node doesn't match the other one, stop.
        // Make sure that the children match as well.
        for (std::size_t i = 0; i < other_node->get_num_children(); ++i) {
            if (i >= curr_node->get_num_children()) {
                return false;
            } else {
                // If the next child symbol is an elipsis, return true.
                if (curr_node->get_child(i)->get_data()->type() == typeid(shaka::Symbol)) { 
                    // If the symbol if an elipsis, then verify that it matches the rest of stuff.
                    auto symbol = shaka::get<shaka::Symbol>(*curr_node->get_child(i)->get_data());
                    if (symbol == elipsis) {
                        if (i == 0) {
                            throw std::runtime_error(
                                "Pattern.matches: elipsis cannot be the first identifier literal to match to."
                            );
                            return false;
                        } else {
                            /// @todo Make sure to bind the rest of the list to the remainder.
                            break;
                        }
                    }
                }
                std::cout << '\t'; 
                if (!matches_recursive(curr_node->get_child(i), other_node->get_child(i))) { return false; }
            }
        }
        // If the current node is a symbol, just match to what the
        // other node is.
        if (curr_node->get_data()->type() == typeid(shaka::Symbol)) { 
            return true;
        }
        // If the current node is a LIST but the other one is not,
        // return false.
        else if (curr_node->get_data()->type() == typeid(shaka::MetaTag)) {
            auto tag = shaka::get<shaka::MetaTag>(*curr_node->get_data());
            if (tag != shaka::MetaTag::LIST && tag != shaka::MetaTag::PROC_CALL) {
                return false;
            }
        }
        return true;
    }

    INodePtr root;
    shaka::Symbol elipsis;
};

/// @brief Represents the tree to substitute into.
/// 
///        Is essentially the same as ProcCall
///        except the literal identifier variables
///        will be bound to their respective contents
///        as detected by the macro before hand,
///        and the macro arguments will not be evaluated
///        before insertion into the tree.
///        
///        The tree will also not be evaluated. Instead,
///        it will simply have its bound symbols substituted
///        for the contents that are pattern-matched on by the
///        `shaka::macro::Pattern`.
class Template {
    Template (INodePtr root) :
        root(root) {}

    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

    /// @brief This will substitute the macro in, given the correct
    ///        identifier variable bindings have already been applied
    ///        to the environment.
    ///
    ///        After substitution, the macro should be ready to evaluate
    ///        normally.
    INodePtr substitute(std::shared_ptr<IEnvironment<Key, Value>> env);

    INodePtr root;
};

/// @brief Represents the implementation of R7RS Scheme transformer macros.
///        It is one of the types that comprise the basic shaka::Data types.
class Macro {
public:

    // Needs to include a pattern-matching component
    // Needs to also include a substitution component
    // Needs to identify stuff.
    //
    //
    // Needs to hold multiple patterns

    /// @brief Represents the pattern-template cases specified in the 
    /// 
    //std::vector<Pattern, Template> cases; 
};

} // namespace macro
} // namespace shaka

#endif // SHAKA_MACRO_MACRO_H
