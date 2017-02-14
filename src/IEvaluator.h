#ifndef SHAKA_EVALUATOR_H
#define SHAKA_EVALUATOR_H

#include <memory>

// #include "IEnvironment.h"
#include "IDataNode.h"

namespace shaka {

/// @note IEvaluatorStrategy class forward declaration is NOT a stub. Do not touch.
class IEvaluatorStrategy;

/// @todo Include the correct IEnvironment interface
class IEnvironment;


/// @brief Interface for the Evaluator class that will evaluate
///        expressions for the `IDataNode` Scheme expression tree.
template <typename NodeData>
class Evaluator {
public:
    Evaluator(std::shared_ptr<IEnvironment> root_node,
               std::shared_ptr<IDataNode<NodeData>> root_env) :
        root_env(root_env),
        current_env(
        root_node(root_node) {}


    /// @brief Delegates the evaluation of a node to a given strategy,
    ///        which is accessed through the IEvaluatorStrategy interface.
    /// 
    /// @note The IEvaluatorStrategy uses polymorphism with a rvalue-reference.
    ///       This is to avoid the use of pointers.
    void evaluate (IEvaluatorStrategy<NodeData>&& strategy) {
        strategy->evaluate(current_node, current_env);
    }
        
private:
    std::shared_ptr<IEnvironment> current_env;
    std::weak_ptr<IDataNode<NodeData>> current_node;
};



} // namespace shaka

#endif // SHAKA_EVALUATOR_H
