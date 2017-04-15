#ifndef SHAKA_CORE_EVAL_DEFINE_H
#define SHAKA_CORE_EVAL_DEFINE_H

#include "core/base/IEvaluatorStrategy.h"

namespace shaka {
namespace eval {

class Define : public shaka::IEvaluatorStrategy {
    virtual NodePtr evaluate(NodePtr node, EnvPtr env) override;
};

} // namespace eval
} // namespace shaka


#endif // SHAKA_CORE_EVAL_DEFINE_H
