#ifndef SHAKA_CORE_BASE_IEVALUATORSTRATEGY_H
#define SHAKA_CORE_BASE_IEVALUATORSTRATEGY_H

#include "core/base/DataNode.h"
#include "core/base/Environment.h"

namespace shaka {

class IEvaluatorStrategy {
public:
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<DataNode>;
    /// @brief Evaluates the current subtree, with the root at the DataNode,
    ///        with the given environment.
    ///
    /// Will throw a C++ std::runtime_error exception if there is an evaluation error.
    ///
    /// @param node
    ///     The DataNode to start evaluating from. Also starts from the root of the tree.
    ///     Nodes will be deleted as they are no longer used, as per the ownership rules of
    ///     `std::shared_ptr`
    /// 
    /// @param env
    ///     The Environment to evaluate the node in. Any variable references will be evaluated
    ///     within the scope of this environment. If a variable is undefined in the current environment,
    ///     the Strategy will attempt to redo the evaluation in the parent environment and so on,
    ///     until it reaches the root environment, which has no parent.
    /// 
    /// @return The shared_ptr to the next node that needs to be evaluated.
    virtual std::shared_ptr<DataNode> evaluate(
        std::shared_ptr<DataNode>       node,
        std::shared_ptr<Environment>    env
    ) = 0;

};


} // namespace shaka

#endif // SHAKA_CORE_BASE_IEVALUATORSTRATEGY_H

