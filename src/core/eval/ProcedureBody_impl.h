#ifndef SHAKA_CORE_EVAL_PROCEDUREBODY_IMPL_H
#define SHAKA_CORE_EVAL_PROCEDUREBODY_IMPL_H

#include "core/base/Core.h"
#include "core/base/Evaluator.h"
#include "core/base/IEvaluatorStrategy.h"

#include "core/eval/ProcedureBody.h" 
#include "core/eval/Expression_impl.h"


namespace shaka { 
/// Encapsulates the EvaluatorStrategy classes

namespace eval {

/// @brief returns a std::shared_ptr to the child node
NodePtr ProcedureBody::evaluate(NodePtr node, EnvPtr env){
    std::cout << "@ProcedureBody" << std::endl;
    // If the root node is LIST, that's right. It's a list of expressions
    // to evaluate.
    NodePtr expr = std::make_shared<shaka::DataNode>(node->get_data());
    if (!node->is_null()) {
        while(!(expr->cdr()->is_null())){
            shaka::Evaluator evaluator ((*expr).car(), env);
            // Evaluate the expression.
            evaluator.evaluate(shaka::eval::Expression());
            expr = (*expr).cdr();
        }
        std::cout << "@ProcedureBody:Arg(" << node->length()-1<< ")" << std::endl;
        // Return the result of evaluating the last expression
        // in the list of expressions.
        shaka::Evaluator evaluator (expr, env);
        auto last_value_ptr = evaluator.evaluate(shaka::eval::Expression());
        return last_value_ptr;
        
    } else {
        throw std::runtime_error("eval/ProcedureBody: Root node is the empty list.");
    }

    return nullptr;
}



} // namespace eval

} // namespace shaka

#endif // SHAKA_CORE_EVAL_PROCEDUREBODY_H
