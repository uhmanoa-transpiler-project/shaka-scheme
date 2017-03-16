#ifndef EVAL_QUOTE_H
#define EVAL_QUOTE_H

#include "IEvaluatorStrategy.h"

#include "Symbol.h"
#include "DataNode.h"

namespace shaka {

class IEvaluatorStrategy;

/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief returns a std::shared_ptr to the child node
class Quote : public IEvaluatorStrategy {
public:
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
	std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env) {

		return node->get_child(0);
	}

};

} // namespace eval

} // namespace shaka

#endif // EVAL_QUOTE_H
