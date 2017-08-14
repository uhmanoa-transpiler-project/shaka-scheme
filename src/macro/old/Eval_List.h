#ifndef SHAKA_EVAL_LIST
#define SHAKA_EVAL_LIST


#include "IEvaluatorStrategy.h"

namespace shaka {
namespace eval {

/// @brief Prints the types of all of the T in the tree.
class List_car : public IEvaluatorStrategy {
public:
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

    /// @brief Prints the type of all the items in the tree recursively.
    std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    ) {
        if (node->get_data()->type() == typeid(shaka::MetaTag)) {
            if (shaka::get<shaka::MetaTag>(*node->get_data()) == shaka::MetaTag::LIST) {
                if (node->get_num_children() == 0) {
                    return node;
                } else {
                    return node->get_child(0);
                }
            }
        } else {
            return node;
        }
    }
};

/// @brief Prints the types of all of the T in the tree.
class List_cdr : public IEvaluatorStrategy {
public:
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

    /// @brief Prints the type of all the items in the tree recursively.
    std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    ) {
        if (node->get_data()->type() == typeid(shaka::MetaTag)) {
            if (shaka::get<shaka::MetaTag>(*node->get_data()) == shaka::MetaTag::LIST) {
                if (node->get_num_children() == 0) {
                    return node;
                } else {
                    auto result = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::MetaTag::LIST);
                    for (std::size_t i = 1; i < node->get_num_children(); ++i) {
                        node->get_child(i)->copy_subtree_onto(result);
                    }
                    return result;
                }
            } else {
                throw std::runtime_error("List_cdr: Cannot get cdr of a non-list and non-atom");
                return nullptr;
            }
        } else {
            throw std::runtime_error("List_cdr: Cannot get cdr of a literal");
            return nullptr;
        }
    }
};

}
}

#endif // SHAKA_EVAL_LIST
