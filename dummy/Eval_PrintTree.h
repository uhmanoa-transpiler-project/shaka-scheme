#ifndef SHAKA_EVAL_PRINTTREE_H
#define SHAKA_EVAL_PRINTTREE_H

#include <type_traits>
#include <iostream>

#include "IEvaluatorStrategy.h"

#include "Symbol.h"
#include "DataNode.h"

#include "EvaluatorStrategyDefinitions.h"

namespace shaka {

/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// @brief Prints the types of all of the T in the tree.
template <std::ostream& out>
class PrintTree : public IEvaluatorStrategy {
public:
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    /// @brief Prints the type of all the items in the tree recursively.
    std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    ) {
        out << node->get_data()->type().name();
        if (node->get_data()->type() == typeid(shaka::Symbol)) {
            out << "(" << shaka::get<shaka::Symbol>(*node->get_data()).get_value() << ')';
        } else if (node->get_data()->type() == typeid(shaka::Number)) {
            out << "()";
        } else if (node->get_data()->type() == typeid(shaka::MetaTag)) {
            out << "(" << static_cast<int>(shaka::get<shaka::MetaTag>(*node->get_data())) << ')';
        }
        out << std::endl;
        for (size_t i = 0; i < node->get_num_children(); ++i) {
            out << '\t';
            this->evaluate(node->get_child(i), env);
        }
        return node;
    }
};

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_PRINTTREE_H
