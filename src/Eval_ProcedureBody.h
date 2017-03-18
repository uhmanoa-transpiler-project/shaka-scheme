#ifndef SHAKA_EVAL_PROCEDUREBODY_H
#define SHAKA_EVAL_PROCEDUREBODY_H

#include "Data.h"
#include "Symbol.h"
#include "DataNode.h"

#include "EvaluatorStrategyDefinitions.h"

#include "Evaluator.h"
#include "IEvaluatorStrategy.h"

#include "Eval_Define.h"


namespace shaka { 
    
/// Encapsulates the EvaluatorStrategy classes
namespace eval {

    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
/// @brief returns a std::shared_ptr to the child node
class ProcedureBody : public IEvaluatorStrategy {
public:
	std::shared_ptr<IDataNode<T>> evaluate(
            std::shared_ptr<IDataNode<T>> node,
			std::shared_ptr<IEnvironment<Key, Value>> env); 

};

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_PROCEDUREBODY_H
