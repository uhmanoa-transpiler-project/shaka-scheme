#ifndef SHAKA_CORE_EVAL_QUOTE_IMPL_H
#define SHAKA_CORE_EVAL_QUOTE_IMPL_H

#include "core/eval/Quote.h"

namespace shaka {
namespace eval {

NodePtr Quote::evaluate(NodePtr list, EnvPtr env) {
    // Turn off env unused warning
    static_cast<void>(env);
    if (!list->is_list()) {
        throw std::runtime_error("eval.Quote: argument is not a list");
        return nullptr;
    }
    std::cout << "@Quote" << std::endl;
    std::cout << *list << std::endl;
    return list->car();
}

} // namespace eval
} // namespace shaka


#endif // SHAKA_CORE_EVAL_QUOTE_H
