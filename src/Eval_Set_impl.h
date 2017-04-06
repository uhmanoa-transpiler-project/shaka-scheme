#ifndef SHAKA_EVAL_SET_IMPL_H
#define SHAKA_EVAL_SET_IMPL_H

#include <type_traits>

#include "IEvaluatorStrategy.h"
#include "IEnvironment.h"

#include "Symbol.h"
#include "DataNode.h"

#include "Evaluator.h"

#include "EvaluatorStrategyDefinitions.h"

#include "Eval_Set.h"
#include "Eval_Expression.h"

#include "Eval_Expression_impl.h"

namespace shaka {

/// Encapsulates the EvaluatorStrategy classes
namespace eval {

using T = shaka::Data;
using Key = shaka::Symbol;
using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

std::shared_ptr<IDataNode<T>> Set::evaluate(
    std::shared_ptr<IDataNode<T>> node,
    std::shared_ptr<IEnvironment<Key, Value>> env
) {
        Key arg = shaka::get<Key>(*node->get_child(0)->get_data());
        shaka::Evaluator evaluator(node->get_child(1), env);
        if(env->get_value(arg) != nullptr)
        {
            env->set_value(
                arg,
                evaluator.evaluate(shaka::eval::Expression())
            );
        }
        else {
            throw std::runtime_error("Set: Cannot set");
        }
        return nullptr;
}

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_SET_H