#ifndef SHAKA_CORE_EVAL_LAMBDA_H
#define SHAKA_CORE_EVAL_LAMBDA_H

#include "core/base/IEvaluatorStrategy.h"

namespace shaka {
namespace eval {

class Lambda : public shaka::IEvaluatorStrategy {
    virtual NodePtr evaluate(NodePtr node, EnvPtr env);
};

} // namespace eval
} // namespace shaka


#endif // SHAKA_CORE_EVAL_LAMBDA_H