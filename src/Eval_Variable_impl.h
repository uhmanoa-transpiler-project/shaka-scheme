#ifndef SHAKA_EVAL_VARIABLE_IMPL_H
#define SHAKA_EVAL_VARIABLE_IMPL_H

#include "Eval_Variable.h"

#include "Evaluator.h"

#include "Eval_Expression_impl.h"

namespace shaka{

namespace eval{

using T = shaka::Data;
using Key = shaka::Symbol;
using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

std::shared_ptr<IDataNode<T>> Variable::evaluate(
        std::shared_ptr<IDataNode<T>> node, 
        std::shared_ptr<IEnvironment<Key,Value>> env) {

    // Lookup the Symbol from the Environment.
    std::cout << "@Variable" << std::endl;
    shaka::Evaluator evaluator(
        env->get_value(shaka::get<Key>(*node->get_data())),
        env
    );

    return evaluator.evaluate(shaka::eval::Expression());
}

}
}

#endif // SHAKA_EVAL_VARIABLE_IMPL_H
