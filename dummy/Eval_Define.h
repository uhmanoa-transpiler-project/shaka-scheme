#ifndef SHAKA_EVAL_DEFINE_H
#define SHAKA_EVAL_DEFINE_H

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
class Define : public IEvaluatorStrategy {
public:
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    /// @brief Prints the type of all the items in the tree recursively.
    std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    ) {
        // Create an evaluate to evaluate the right child node.
        shaka::Evaluator evaluator(node->get_child(1), env);
        // Set the environment[symbol] entry to the result of
        // evaluation of the expression term.
        env->set_value(
            shaka::get<Key>(*node->get_child(0)->get_data()),
            evaluator.evaluate(shaka::eval::Expression())
         );
        return nullptr;
    }
};

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_DEFINE_H
