/*
#ifndef SHAKA_ITREE_H
#define SHAKA_ITREE_H

#include <memory>

namespace shaka {

/// @brief The interface for our internal `Tree` data structure.
///
/// The `ITree` requires use of `std::shared_ptr` for thread safety.
template <typename T>
struct ITree {
    /// @brief Overloadable destructor.
    virtual ~ITree() {}

    virtual std::shared_ptr<ITree> get_parent() = 0;
    virtual std::shared_ptr<ITree> insert_child(
        int                         index,
        std::shared_ptr<ITree<T>>   node
    ) = 0;
    virtual std::shared_ptr<ITree> push_child(T data) = 0;
    virtual std::shared_ptr<ITree> remove_child(int index) = 0;
    virtual std::shared_ptr<ITree> get_child(int index) = 0;
    virtual std::shared_ptr<ITree> get_last_child() = 0;
    virtual std::size_t            get_num_children() = 0;
    virtual std::shared_ptr<T>     get_node() = 0;
    virtual std::shared_ptr<T>     set_node(T data) = 0;
};

} // namespace shaka

#endif // SHAKA_ITREE_H

*/