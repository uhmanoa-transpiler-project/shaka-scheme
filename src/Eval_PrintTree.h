#ifndef SHAKA_EVAL_PRINTTREE_H
#define SHAKA_EVAL_PRINTTREE_H

#include <type_traits>

#include "IEvaluatorStrategy.h"

namespace shaka {

/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief Prints the types of all of the T in the tree.
template <typename T, typename Key, typename Value, std::ostream& out>
class PrintTree : public shaka::IEvaluatorStrategy<T, Key, Value> {

    /// @brief Prints the type of all the items in the tree recursively.
    std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    ) {
        out << node->get_data()->type().name() << std::endl;
        for (size_t i = 0; i < node->get_num_children(); ++i) {
            out << '\t';
            this->evaluate(node->get_child(0), env);
        }
        return node;
    }
};

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_PRINTTREE_H
