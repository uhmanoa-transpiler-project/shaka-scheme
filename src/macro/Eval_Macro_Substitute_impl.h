#ifndef SHAKA_EVAL_MACRO_SUBSTITUTE_IMPL_H
#define SHAKA_EVAL_MACRO_SUBSTITUTE_IMPL_H

#include "IEvaluatorStrategy.h"

namespace shaka {
namespace eval {

using T = shaka::Data;
using Key = shaka::Symbol;
using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

std::shared_ptr<IDataNode<shaka::Data> Macro_Substitute::evaluate(
    std::shared_ptr<IDataNode<T>>               node,
    std::shared_ptr<IEnvironment<Key, Value>>   env
) {
    auto result = std::make_shared<DataNode<T>>(node->get_data());
    // For each node in the tree, substitute the symbols with
    // their bindings in the environment, a special environment
    // that holds the bindings from the macro literals
    // to their bound expressions to replace with.
    for (std::size_t i = node->get_num_children(); ++i) {
        // If the current child node is a symbol, check if it's in the environment.
        // If it is, then replace it with its binding.
        if (auto* ptr = shaka::get<shaka::Symbol>(node->get_child(i)->get_data().get())) {
            if (env->contains(*ptr)) {
               env[*ptr]->copy_subtree_onto(result);
            } else {
                result->push_child(node->get_child(i)->get_data());
            }
        } else {
            result->push_child(node->get_child(i)->get_data());
        }
    }
}

}
}

#endif // SHAKA_EVAL_MACRO_SUBSTITUTE_IMPL_H
