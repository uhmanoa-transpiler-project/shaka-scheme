#ifndef SHAKA_EVAL_PROCCALL_H
#define SHAKA_EVAL_PROCCALL_H

#include <type_traits>

#include "IEvaluatorStrategy.h"
#include "IEnvironment.h"

#include "Symbol.h"
#include "DataNode.h"

#include "Evaluator.h"

#include "EvaluatorStrategyDefinitions.h"

#include "Eval_Expression.h"

// attempts to get the procedure bound in the current environment
// and call it on the arguments condained as the child nodes of the
// list node that the procedure is called on
// returns a pointer to the list node with its child node(s)
// updated to be the result(s) of the procedure call

namespace shaka {
namespace eval {

class Proc_Call : public shaka::IEvaluatorStrategy {
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

    /// @brief Evaluates a procedure call within the current environment
    std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    ); 
};
} // namespace eval
} // namespace shaka
#endif // SHAKA_EVAL_PROCCALL_H
