#ifndef SHAKA_CORE_EVAL_DEFINE_IMPL_H
#define SHAKA_CORE_EVAL_DEFINE_IMPL_H

#include "core/eval/Define.h"
#include "core/eval/Expression.h"

namespace shaka {
namespace eval {

NodePtr Define::evaluate(NodePtr list, EnvPtr env) {
    //std::cout << "@Define" << std::endl;
    //std::cout << *list << std::endl;
    if (!list->is_list()) {
        throw std::runtime_error("eval.Define: argument is not a list");
        return nullptr;
    }
    if (list->length() != 2) {
        throw std::runtime_error("eval.Define: argument must be list of length 2");
        return nullptr;
    }
    // Check if the first item is a symbol
    if (list->car()->is_symbol()) {
        // Get the key and the value, and store in the environment
        auto key = get<Symbol>(list->car()->get_data());
        auto value = list->cdr()->car();
        //std::cout << "Pre-evaluaton: " << *value << std::endl;
        // Evaluate the value with the expression, and
        auto evaluated = Evaluator(value, env).evaluate(eval::Expression());
        //std::cout << "Post_evaluation: " << *evaluated << std::endl;
        env->set_value(key, evaluated);
        //std::cout << "Key:" << key << " | Value: " << *env->get_value(key) << std::endl;
    } else {
        // If the first item is not a symbol, raise an exception
        throw std::runtime_error("eval.Define: expected a Symbol as identifier");
    }
    return nullptr;
}

} // namespace eval
} // namespace shaka


#endif // SHAKA_CORE_EVAL_DEFINE_H
