#ifndef SHAKA_CORE_EVAL_DEFINE_IMPL_H
#define SHAKA_CORE_EVAL_DEFINE_IMPL_H

#include "core/eval/Define.h"

namespace shaka {
namespace eval {

NodePtr Define::evaluate(NodePtr list, EnvPtr env) {
    if (!list->is_list()) {
        throw std::runtime_error("eval.Define: argument is not a list");
        return nullptr;
    }
    // Check if the first item is a symbol
    if (list->car()->is_symbol()) {
        // Get the key and the value, and store in the environment
        auto key = get<Symbol>(list->car()->get_data());
        auto value = list->cdr()->get_data();
        env->set_value(key, value);
    } else {
        // If the first item is not a symbol, raise an exception
        throw std::runtime_error("eval.Define: key is not a Symbol");
    }
    return nullptr;
}

} // namespace eval
} // namespace shaka


#endif // SHAKA_CORE_EVAL_DEFINE_H
