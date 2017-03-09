#ifndef EVAL_QUOTE_H
#define EVAL_QUOTE_H
#include "IEvaluatorStrategy.h"

namespace shaka {

/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief returns a std::shared_ptr to the child node
template <typename T, typename Key, typename Value > 
class Quote : public shaka::IEvaluatorStrategy<T, Key, Value> {
public:
	std::shared_ptr<IDataNode<T>> evaluate(std::shared_ptr<IDataNode<T>> node,
			std::shared_ptr<IEnvironment<Key, Value>> env) {
		return node->get_child(0);

	}

};

} // namespace eval

} // namespace shaka

#endif // EVAL_QUOTE_H
