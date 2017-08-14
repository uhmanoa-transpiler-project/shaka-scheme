#ifndef SHAKA_EVAL_EXPRESSION_IMPL_H
#define SHAKA_EVAL_EXPRESSION_IMPL_H

#include "core/base/Core.h"

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
    //std::cout << "@Expression" << std::endl;
    //std::cout << "\t" << *node << std::endl; 

    if (node == nullptr) {
        throw std::runtime_error("eval.Expression: node is nullptr");
        return nullptr;
    }


	if (node->is_null()) {
		//std::cout << "@Expression ==> EmptyList (Literal)" << std::endl;
		return node;
	
	}

	else if (node->is_symbol()) {
		//std::cout << "@Expression ==> Symbol" << std::endl;
		return evaluator.evaluate(shaka::eval::Variable());
	}

	else if (node->is_number()) {
		//std::cout << "@Expression ==> Number" << std::endl;
		return node;
	}

	else if (node->is_string()) {
		//std::cout << "@Expression ==> String" << std::endl;
		return node;
	}

	else if (node->is_boolean()) {
		//std::cout << "@Expression ==> Boolean" << std::endl;
		return node;
	}

	else if (node->is_scheme_procedure()) {
		//std::cout << "@Expression ==> Procedure" << std::endl;
		return node;
	}

    else if (node->is_native_procedure()) {
        //std::cout << "@Expression ==> NativeProcedure" << std::endl;
        return node;
    }

    else if (node->is_primitive_procedure()) {
        //std::cout << "@Expression ==> PrimitiveProcedure" << std::endl;
        return node;
    }

	else if (node->is_list()) {
		//std::cout << "@Expression ==> List" << std::endl;
        //std::cout << "node: " << *node << std::endl;
		shaka::Evaluator first_evaluator(node->car(), env);
        //std::cout << "node->car: " << *node->car() << std::endl;
        //std::cout << "node->cdr: " << *node->cdr() << std::endl;
		NodePtr inner_result = first_evaluator.evaluate(shaka::eval::Expression());
        if (inner_result->is_procedure()) {
            NodePtr new_node = std::make_shared<DataNode>(*inner_result, *node->cdr());
            //std::cout << "new node: " << *new_node << std::endl;
            shaka::Evaluator call_eval(new_node, env);
            return call_eval.evaluate(shaka::eval::ProcCall());
        }
        else {
            throw std::runtime_error(
                "eval.Expression: Procedure call does not have procedure operand");
            return nullptr;
        }
        /*
		NodePtr new_node = std::make_shared<DataNode>(*inner_result, *node->cdr());
        std::cout << "new node: " << *new_node << std::endl;
		shaka::Evaluator new_node_evaluator(new_node, env);
		return new_node_evaluator.evaluate(shaka::eval::Expression());
        */
	}
	
	else {
        throw std::runtime_error("Expression: Top-level expression type not supported.");
        return nullptr;
    }

}


} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_EXPRESSION_H
