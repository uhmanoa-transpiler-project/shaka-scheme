#ifndef SHAKA_EVALUATOR_H
#define SHAKA_EVALUATOR_H

#include <memory>

// #include "IEnvironment.h"
#include "IDataNode.h"

namespace shaka {


/// @todo Include the correct IEnvironment interface
class IEnvironment;


/// @brief Interface for the Evaluator class that will evaluate
///        expressions for the `IDataNode` Scheme expression tree.
template <typename NodeData>
class Evaluator {
    Evaluator(std::shared_ptr<IEnvironment> root_node,
               std::shared_ptr<IDataNode<NodeData>> root_env) :
        root_env(root_env),
        current_env(
        root_node(root_node) {}


    void evaluator (IEvaluatorStrategy strategy) {
        strategy->evaluate(current_node, current_env);
    }
        

    std::shared_ptr<IEnvironment> current_env;
    std::weak_ptr<IDataNode<NodeData>> current_node;
};



} // namespace shaka

#endif // SHAKA_EVALUATOR_H
