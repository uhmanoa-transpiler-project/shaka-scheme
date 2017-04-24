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
    //std::cout << "@ProcedureBody" << std::endl;
    // Iterate through the list of expressions in the body.
    NodePtr it = node;
    //env->print_bindings(std::cout);
    // First of all, the body must be valid.
    if (!it->is_null()) {
        // While we are not at the last expression, evaluate it.
        while(!it->is_pair()){
            //std::cout << "@ProcedureBody.expr: " << *it->car() << std::endl;
            shaka::Evaluator evaluator (it->car(), env);
            // Evaluate the expression.
            evaluator.evaluate(shaka::eval::Expression());
            it = it->cdr();
        }
        // Return the result of evaluating the last expression
        // in the list of expressions.
        //std::cout << "@ProcedureBody.last_expr: " << *it->car() << std::endl;
        shaka::Evaluator evaluator (it->car(), env);
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
