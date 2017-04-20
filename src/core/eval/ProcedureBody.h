#ifndef SHAKA_CORE_EVAL_PROCEDUREBODY_H
#define SHAKA_CORE_EVAL_PROCEDUREBODY_H

#include "core/base/DataNode.h"
#include "core/base/IEvaluatorStrategy.h"



namespace shaka { 
/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief returns a std::shared_ptr to the child node
class ProcedureBody : public IEvaluatorStrategy {
public:
    virtual NodePtr evaluate(NodePtr node, EnvPtr env);

};

} // namespace eval

} // namespace shaka

#endif // SHAKA_CORE_EVAL_PROCEDUREBODY_H