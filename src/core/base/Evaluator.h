#ifndef SHAKA_CORE_BASE_EVALUATOR_H
#define SHAKA_CORE_BASE_EVALUATOR_H

#include <memory>

#include "core/base/DataNode.h"

#include "core/base/IEvaluatorStrategy.h"

namespace shaka {

/// @note IEvaluatorStrategy class forward declaration is NOT a stub. Do not touch.
class IEvaluatorStrategy;

/// @brief Interface for the Evaluator class that will evaluate
///        expressions for the `IDataNode` Scheme expression tree.
class Evaluator {
public:
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::DataNode>;

    Evaluator(std::shared_ptr<DataNode> root_node,
              std::shared_ptr<Environment> root_env) :
        current_env(root_env),
        current_node(root_node) {}


    /// @brief Delegates the evaluation of a node to a given strategy,
    ///        which is accessed through the IEvaluatorStrategy interface.
    /// 
    /// @note The IEvaluatorStrategy uses polymorphism with a rvalue-reference.
    ///       This is to avoid the use of pointers.
    NodePtr evaluate(IEvaluatorStrategy&& strategy) {
        /// Sets the current node's result to the result of evaluating the
        /// current node.
        return strategy.evaluate(current_node, current_env);
    }

    /// @brief Returns the `current_node`
    NodePtr get_node() {
        return this->current_node;
    }
        
private:
    std::shared_ptr<Environment> current_env;
    NodePtr current_node;
};


} // namespace shaka

#endif // SHAKA_CORE_BASE_EVALUATOR_H
