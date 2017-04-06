
#ifndef SHAKA_EVAL_LAMBDA_H
#define SHAKA_EVAL_LAMBDA_H

#include <type_traits>
#include <stdexcept>
#include <map>
#include "IEvaluatorStrategy.h"
#include "IProcedure.h"

#include"Procedure.h"
#include "Eval_Expression_impl.h"

namespace shaka {

/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// brief Evaluates the Lambda procedure call
/// Creates a Procedure object by calling the Procedure constructor

class Lambda : public shaka::IEvaluatorStrategy {
public:
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    );
};

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_LAMBDA_H