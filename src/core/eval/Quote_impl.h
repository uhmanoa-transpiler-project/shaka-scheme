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
    // Check if the first item is a symbol
    if (list->car()->is_symbol()) {
        // Check if the symbol is "quote". If so, return cdr.
        auto key = get<Symbol>(list->car()->get_data());
        if (key == Symbol("quote")) {
            if (list->length() != 2) {
                throw std::runtime_error("eval.Quote: incorrect number of arguments");
            }
            return list->cdr()->car();
        }
        else {
            throw std::runtime_error("eval.Quote: list does not begin with Symbol(quote)");
            return nullptr;
        }
    } else {
        // If the first item is not a symbol, raise an exception
        throw std::runtime_error("eval.Quote: key is not a Symbol");
        return nullptr;
    }
}

} // namespace eval
} // namespace shaka


#endif // SHAKA_CORE_EVAL_QUOTE_H
