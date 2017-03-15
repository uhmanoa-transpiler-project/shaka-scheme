#ifndef SHAKA_EVAL_VARIABLE_H
#define SHAKA_EVAL_VARIABLE_H

#include "IEvaluatorStrategy.h"
#include "Symbol.h"
#include "DataNode.h"
#include "IDataNode.h"
#include "Environment.h"
#include <memory>
#include <type_traits>
namespace shaka{

namespace eval{
template <typename T, typename Key, typename Value>
class Variable : public shaka::IEvaluatorStrategy<T, Key, Value> {
public: 
	std::shared_ptr<IDataNode<T>> evaluate(
			std::shared_ptr<IDataNode<T>> node, 
			std::shared_ptr<IEnvironment<Key,Value>> env){
	
		return env->get_value(shaka::get<Key>(*node->get_data()));
	}



};

}
}
#endif
