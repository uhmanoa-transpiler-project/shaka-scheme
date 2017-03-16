#ifndef SHAKA_EVAL_VARIABLE_H
#define SHAKA_EVAL_VARIABLE_H

#include <memory>
#include <type_traits>

#include "IEvaluatorStrategy.h"
#include "Symbol.h"
#include "IDataNode.h"
#include "IEnvironment.h"

#include "Symbol.h"
#include "DataNode.h"

#include "EvaluatorStrategyDefinitions.h"

namespace shaka{

namespace eval{

class Variable : public IEvaluatorStrategy {
public: 
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

	std::shared_ptr<IDataNode<T>> evaluate(
			std::shared_ptr<IDataNode<T>> node, 
			std::shared_ptr<IEnvironment<Key,Value>> env){
	
		return env->get_value(shaka::get<Key>(*node->get_data()));
	}



};

}
}
#endif
