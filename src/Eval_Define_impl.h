#ifndef SHAKA_EVAL_DEFINE_IMPL_H
#define SHAKA_EVAL_DEFINE_IMPL_H

#include <type_traits>

#include "IEvaluatorStrategy.h"
#include "IEnvironment.h"

#include "Symbol.h"
#include "DataNode.h"

#include "Evaluator.h"

#include "EvaluatorStrategyDefinitions.h"

#include "Eval_Define.h"
#include "Eval_Expression.h"

#include "Eval_Expression_impl.h"

namespace shaka {

/// Encapsulates the EvaluatorStrategy classes
namespace eval {

using T = shaka::Data;
using Key = shaka::Symbol;
using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

std::shared_ptr<IDataNode<T>> Define::evaluate(
    std::shared_ptr<IDataNode<T>> node,
    std::shared_ptr<IEnvironment<Key, Value>> env
) {
    // Create an evaluate to evaluate the right child node.
    shaka::Evaluator evaluator(node->get_child(1), env);
    // Set the environment[symbol] entry to the result of
    // evaluation of the expression term.
    std::cout << "@Eval_Define" << std::endl; 
    env->set_value(
        shaka::get<Key>(*node->get_child(0)->get_data()),
        evaluator.evaluate(shaka::eval::Expression())
     );
    return nullptr;
}

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_DEFINE_H
