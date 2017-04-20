#ifndef SHAKA_EVAL_EXPRESSION_IMPL_H
#define SHAKA_EVAL_EXPRESSION_IMPL_H

#include "core/eval/Expression.h"
#include "core/base/Procedure.h"
#include "core/base/Procedure_impl.h"
#include "core/eval/Proccall_impl.h"
#include "core/proc/primitives.h"


namespace shaka { 
    
/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief returns a std::shared_ptr to the child node
NodePtr Expression::evaluate(
    NodePtr node,
    EnvPtr env
) {

    shaka::Evaluator evaluator(node, env);
   // std::cout << "@Expression" << std::endl;
    //evaluator.evaluate(shaka::eval::PrintTree<std::cout>());
	
	if (node->is_null()) {
		std::cout << "@Expression ==> EmptyList (Literal)" << std::endl;
		return node;
	
	}

	else if (node->car()->is_symbol() && node->length() == 1) {
		std::cout << "@Expression ==> Symbol" << std::endl;
		return evaluator.evaluate(shaka::eval::Variable());
	}

	else if (node->car()->is_number() && node->length() == 1) {
		std::cout << "@Expression ==> Number" << std::endl;
		return node;
	}

	else if (node->car()->is_string() && node->length() == 1) {
		std::cout << "@Expression ==> String" << std::endl;
		return node;
	}

	else if (node->car()->is_boolean() && node->length() == 1) {
		std::cout << "@Expression ==> Boolean" << std::endl;
		return node;
	}

	else if (node->car()->get_data().type() == typeid(shaka::Procedure) && node->length() == 1) {
		std::cout << "@Expression ==> Procedure" << std::endl;
		return node;
	}

	else if (node->car()->is_symbol()) {
		std::cout << "@Expression ==> Procedure Call" << std::endl;
		return evaluator.evaluate(shaka::eval::ProcCall());
	
	}
	
	else if (node->car()->is_list()) {
		std::cout << "@Expression ==> List" << std::endl;
		shaka::Evaluator nested_evaluator(node->car(), env);
		NodePtr inner_result = nested_evaluator.evaluate(shaka::eval::Expression());
		NodePtr new_node = std::make_shared<DataNode>(*inner_result, *node->cdr());
		shaka::Evaluator new_node_evaluator(new_node, env);
		return new_node_evaluator.evaluate(shaka::eval::Expression());
	}
	
	else {
        throw std::runtime_error("Expression: Top-level expression type not supported.");
        return nullptr;
    }

}


} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_EXPRESSION_H
