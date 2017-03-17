#ifndef SHAKA_IEVALUATORSTRATEGY_H
#define SHAKA_IEVALUATORSTRATEGY_H

#include "DataNode.h"
#include "Environment.h"

/// @todo Replace IEnvironment stub with the real Environment interface.

namespace shaka {

namespace eval {

class Expression; 

}

class IEvaluatorStrategy {
public:
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
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
    virtual std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    ) = 0;

};



} // namespace shaka

#endif // SHAKA_IEVALUATORSTRATEGY_H

