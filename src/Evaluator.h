#ifndef SHAKA_EVALUATOR_H
#define SHAKA_EVALUATOR_H

#include <memory>

// #include "IEnvironment.h"
#include "IDataNode.h"

namespace shaka {

/// @note IEvaluatorStrategy class forward declaration is NOT a stub. Do not touch.
template <typename T, typename Key, typename Value>
class IEvaluatorStrategy;



/// @brief Interface for the Evaluator class that will evaluate
///        expressions for the `IDataNode` Scheme expression tree.
template <typename T, typename Key, typename Value>
class Evaluator {
public:
    Evaluator(std::shared_ptr<IEnvironment<Key, Value>> root_env,
               std::shared_ptr<IDataNode<T>> root_node) :
        current_env(root_env),
        current_node(root_node) {}


    /// @brief Delegates the evaluation of a node to a given strategy,
    ///        which is accessed through the IEvaluatorStrategy interface.
    /// 
    /// @note The IEvaluatorStrategy uses polymorphism with a rvalue-reference.
    ///       This is to avoid the use of pointers.
    void evaluate(IEvaluatorStrategy<T, Key, Value>&& strategy) {
        /// Sets the current node's result to the result of evaluating the
        /// current node.
        strategy.evaluate(current_node, current_env);
    }

    /// @brief Returns the `current_node`
    std::shared_ptr<IDataNode<T>> get_node() {
        return this->current_node;
    }
        
private:
    std::shared_ptr<IEnvironment<Key, Value>> current_env;
    std::shared_ptr<IDataNode<T>> current_node;
};



} // namespace shaka

#endif // SHAKA_EVALUATOR_H
