#ifndef SHAKA_EVAL_PRINTTREE_H
#define SHAKA_EVAL_PRINTTREE_H

#include "IEvaluatorStrategy.h"

namespace shaka {

/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief Prints all of the NodeData in the tree.
template <typename NodeData, typename Key, typename Value, std::ostream& out>
class PrintTree : public shaka::IEvaluatorStrategy<NodeData, Key, Value> {

    /// @brief Prints the type of all the items in the tree recursively.
    std::shared_ptr<IDataNode<NodeData>> evaluate(
        std::shared_ptr<IDataNode<NodeData>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    ) {
        out << node->get_data().type();
        for (int i = 0; i < node->get_num_children(); ++i) {
            out << '\t';
            this->evaluate(node->get_child(0), env);
        }
        return node;
    }
};

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_PRINTTREE_H
