#ifndef SHAKA_EVAL_EXPRESSION_H
#define SHAKA_EVAL_EXPRESSION_H

#include "core/base/Data.h"
#include "core/base/Symbol.h"
#include "core/base/DataNode.h"


#include "core/base/Evaluator.h"
#include "core/base/IEvaluatorStrategy.h"


#include "core/eval/Define.h"
#include "core/eval/Variable.h"
#include "core/eval/Quote.h"
//#include "core/eval/Lambda.h"
#include "core/eval/Proccall.h"

namespace shaka { 
    
/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief returns a std::shared_ptr to the child node
class Expression : public shaka::IEvaluatorStrategy {
public:

	virtual NodePtr evaluate(NodePtr node, EnvPtr env); 

};

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_EXPRESSION_H
