#ifndef SHAKA_EVAL_SET_H
#define SHAKA_EVAL_SET_H

#include <type_traits>

#include "IEvaluatorStrategy.h"
#include "IEnvironment.h"

#include "Symbol.h"
#include "DataNode.h"

#include "Evaluator.h"

#include "EvaluatorStrategyDefinitions.h"

#include "Eval_Expression.h"

namespace shaka {

/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief Prints the types of all of the T in the tree.
class Set : public IEvaluatorStrategy {
public:
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

    /// @brief Prints the type of all the items in the tree recursively.
    std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    ); 
};

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_SET_H