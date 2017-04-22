#ifndef SHAKA_CORE_EVAL_SETUPTOPLEVEL_H
#define SHAKA_CORE_EVAL_SETUPTOPLEVEL_H


#include "core/base/IEvaluatorStrategy.h"
#include "core/base/Evaluator.h"

namespace shaka {

namespace eval {

class SetupTopLevel : public IEvaluatorStrategy {
public: 
	using Key = shaka::Symbol;
	using Value = std::shared_ptr<shaka::DataNode>;

	virtual std::shared_ptr<shaka::DataNode> evaluate(
			std::shared_ptr<shaka::DataNode> node,
			std::shared_ptr<shaka::Environment> env);

};

} //namespace eval

} //namespace shaka


#endif // SHAKA_CORE_EVAL_SETUPTOPLEVEL_H
