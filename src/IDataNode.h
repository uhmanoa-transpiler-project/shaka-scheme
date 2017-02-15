#ifndef SHAKA_IDATANODE_H
#define SHAKA_IDATANODE_H

#include <boost/variant/get.hpp>

#include <memory>

namespace shaka {

/// @brief The interface for our internal `DataNode` data structure.
///
/// Each IDataNode will have children and parents.
template <typename T>
class IDataNode : public std::enable_shared_from_this<IDataNode<T>> {
public:
    /// @brief Overloadable destructor.
    virtual ~IDataNode() {}

    virtual std::shared_ptr<IDataNode>  get_parent() = 0;
    virtual void                        set_parent(
        std::shared_ptr<IDataNode<T>> node
    ) = 0;
    virtual std::shared_ptr<IDataNode>  insert_child(
        int                             index,
        std::shared_ptr<IDataNode<T>>   node
    ) = 0;
    virtual std::shared_ptr<IDataNode>  push_child(T data) = 0;
    virtual std::shared_ptr<IDataNode>  remove_child(int index) = 0;
    virtual std::shared_ptr<IDataNode>  get_child(int index) = 0;
    virtual std::shared_ptr<IDataNode>  get_last_child() = 0;
    virtual std::size_t                 get_num_children() = 0;
    virtual std::shared_ptr<T>          get_data() = 0;
    virtual std::shared_ptr<T>          set_data(T data) = 0;

};

using boost::get;

} // namespace shaka


#endif // SHAKA_IDATANODE_H
