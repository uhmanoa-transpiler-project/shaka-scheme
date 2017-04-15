#ifndef SHAKA_CORE_EVAL_VARIABLE_H
#define SHAKA_CORE_EVAL_VARIABLE_H

#include "core/base/IEvaluatorStrategy.h"

namespace shaka {
namespace eval {

class Variable : public shaka::IEvaluatorStrategy {
    virtual NodePtr evaluate(NodePtr node, EnvPtr env) override;
};

} // namespace eval
} // namespace shaka


#endif // SHAKA_CORE_EVAL_VARIABLE_H
