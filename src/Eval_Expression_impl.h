#ifndef SHAKA_EVAL_EXPRESSION_IMPL_H
#define SHAKA_EVAL_EXPRESSION_IMPL_H

#include "Data.h"
#include "Symbol.h"
#include "DataNode.h"

#include "EvaluatorStrategyDefinitions.h"

#include "Evaluator.h"
#include "IEvaluatorStrategy.h"

#include "Eval_Define.h"
#include "Eval_Variable.h"
#include "Eval_Quote.h"
#include "Eval_Lambda.h"
#include "Eval_Proccall.h"

#include "Eval_Expression.h"

#include "Eval_PrintTree.h"

#include "Eval_Define_impl.h"
#include "Eval_Variable_impl.h"
#include "Eval_Proccall_impl.h"
#include "Eval_Lambda_impl.h"


namespace shaka { 
    
/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief returns a std::shared_ptr to the child node

using T = shaka::Data;
using Key = shaka::Symbol;
using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

std::shared_ptr<IDataNode<T>> Expression::evaluate(
    std::shared_ptr<IDataNode<T>> node,
    std::shared_ptr<IEnvironment<Key, Value>> env
) {

    shaka::Evaluator evaluator(node, env);
    std::cout << "@Expression" << std::endl;
    evaluator.evaluate(shaka::eval::PrintTree<std::cout>());

    const auto& type = node->get_data()->type();

    if (type == typeid(shaka::MetaTag)) {
        auto tag = shaka::get<shaka::MetaTag>(*node->get_data());
        if (tag == shaka::MetaTag::DEFINE) {
            std::cout << "@Expression ==> Define" << std::endl;
            return evaluator.evaluate(shaka::eval::Define());
        } else if (tag == shaka::MetaTag::QUOTE) {
            std::cout << "@Expression ==> Quote" << std::endl;
            return evaluator.evaluate(shaka::eval::Quote());
        } else if (tag == shaka::MetaTag::LIST) {
            std::cout << "@Expression ==> List (Literal)" << std::endl;
            return node;
        } else if (tag == shaka::MetaTag::LAMBDA) {
			std::cout << "@Expression ==> Lambda (Literal)" << std::endl;
			return evaluator.evaluate(shaka::eval::Lambda());
		} else if (tag == shaka::MetaTag::PROC_CALL) {
			std::cout << "@Expression ==> Procedure Call" << std::endl;
			return evaluator.evaluate(shaka::eval::Proc_Call());
		} else {
            throw std::runtime_error("Expression: Invalid MetaTag option.");
            return nullptr;
        }
    }

    else if (type == typeid(shaka::Symbol)) {
        std::cout << "@Expression ==> Symbol" << std::endl;
        return evaluator.evaluate(shaka::eval::Variable());
    }

    else if (type == typeid(shaka::Number)) {
        std::cout << "@Expression ==> Number" << std::endl;
        return node;
    }

    else if (type == typeid(shaka::Procedure)) {
        std::cout << "@Expression ==> Procedure" << std::endl;
        return node;
    }

	else if (type == typeid(shaka::String)) {
		std::cout << "@Expression ==> String" << std::endl;
		return node;
	}

    else {
        throw std::runtime_error("Expression: Top-level expression type not supported.");
        return nullptr;
    }

}


} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_EXPRESSION_H
