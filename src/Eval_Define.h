#ifndef SHAKA_EVAL_PRINTTREE_H
#define SHAKA_EVAL_PRINTTREE_H

#include <type_traits>

#include "IEvaluatorStrategy.h"
#include "Environment.h"

namespace shaka {

/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief Prints the types of all of the T in the tree.
template <typename T, typename Key, typename Value>
class Define : public shaka::IEvaluatorStrategy<T, Key, Value> {

    /// @brief Prints the type of all the items in the tree recursively.
    std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>>& node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    ) {
        env->set_value(
            shaka::get<Key>(*node->get_child(0)->get_data()),
            node->get_child(1)
         );
        return nullptr;
    }
};

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_PRINTTREE_H
