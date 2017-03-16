#ifndef EVAL_EXPRESSION_H
#define EVAL_EXPRESSION_H
#include "IEvaluatorStrategy.h"
#include "EvaluatorStrategies.h"
#include "Eval_Quote.h"
namespace shaka {

/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief returns a std::shared_ptr to the child node
template <typename T, typename Key, typename Value > 
class Expression : public shaka::IEvaluatorStrategy<T, Key, Value> {
public:
	std::shared_ptr<IDataNode<T>> evaluate(std::shared_ptr<IDataNode<T>> node,
			std::shared_ptr<IEnvironment<Key, Value>> env) {

        if (node->get_data()->type() == typeid(shaka::MetaTag::DEFINE)) {
			return shaka::eval::Define<T, Key, Value>().evaluate(node, env);
        }

		else if (node->get_data()->type() == typeid(shaka::Symbol)) {
			return shaka::eval::Variable<T, Key, Value>().evaluate(node, env);
		}

		else if (node->get_data()->type() == typeid(shaka::MetaTag::QUOTE)) {
			return shaka::eval::Quote<T, Key, Value>().evaluate(node, env);
		}

		

	}

};

} // namespace eval

} // namespace shaka

#endif // EVAL_EXPRESSION_H
