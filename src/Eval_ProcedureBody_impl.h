#ifndef SHAKA_EVAL_PROCEDUREBODY_IMPL_H
#define SHAKA_EVAL_PROCEDUREBODY_IMPL_H

#include "Data.h"
#include "Symbol.h"
#include "DataNode.h"

#include "EvaluatorStrategyDefinitions.h"

#include "Evaluator.h"
#include "IEvaluatorStrategy.h"

#include "Eval_Expression.h"
#include "Eval_ProcedureBody.h" 

#include "Eval_Expression_impl.h"

namespace shaka { 
    
/// Encapsulates the EvaluatorStrategy classes
namespace eval {

using T = shaka::Data;
using Key = shaka::Symbol;
using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

/// @brief Evaluates the list of expressions.
std::shared_ptr<IDataNode<T>> ProcedureBody::evaluate(
    std::shared_ptr<IDataNode<T>> node,
    std::shared_ptr<IEnvironment<Key, Value>> env
) {
    std::cout << "@ProcedureBody" << std::endl;
    // If the root node is LIST, that's right. It's a list of expressions
    // to evaluate.
    if (auto* ptr = shaka::get<shaka::MetaTag>(node->get_data().get())) {
        if (!ptr) { throw std::runtime_error("Eval_ProcedureBody: Root node is null"); }
        // For each child, evaluate with shaka::eval::Expression()
        for (std::size_t i = 0; i < node->get_num_children()-1; ++i) {
            std::cout << "@ProcedureBody:Arg(" << i << ")" << std::endl;
            // Setup the current expression to evaluate.
            shaka::Evaluator evaluator (node->get_child(i), env);
            // Evaluate the expression.
            evaluator.evaluate(shaka::eval::Expression());
        }
        std::cout << "@ProcedureBody:Arg(" << node->get_num_children()-1 << ")" << std::endl;
        // Return the result of evaluating the last expression
        // in the list of expressions.
        shaka::Evaluator evaluator (node->get_child(node->get_num_children()-1), env);
        auto last_value_ptr = evaluator.evaluate(shaka::eval::Expression());
        return last_value_ptr;
        
    } else {
        throw std::runtime_error("Eval_ProcedureBody: Did not get a list as the root node.");
    }

    return nullptr;
}

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_PROCEDUREBODY_IMPL_H
