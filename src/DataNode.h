#ifndef SHAKA_DATANODE_H
#define SHAKA_DATANODE_H

#include <vector>

#include <boost/variant.hpp>

#include "IDataNode.h"

namespace shaka {

/// @brief Auxillary "type-tags" used to decide whether the
/// contained type should have children, according to the sematnics
/// of the Meta Tag.
///
/// For example, an `ATOM` should have no children nodes, but
/// a `LIST` should have links to its children as a vector of pointers.
enum class MetaTag : int {
    LIST,
    PROCEDURE,
    IF,
    PAIR,
    VECTOR,
    BYTEVECTOR,
    NULL_LIST,
    ATOM,
    RECORD
};

/// @brief `boost::variant` is being re-aliased for the
/// readability purposes of the project.
using Data = 
boost::variant<
    bool,
    int,
    std::string,
    MetaTag
>;


/// @brief The central data structure for a Scheme object.
///
/// The Shaka Scheme data node implements the core data structure
/// for all objects by providing a sum (variant) type. To leverage
/// already existing code, `boost::variant` from the Boost C++ Library
/// has been adopted to handle that part of the internal data structure.
///
/// DataNode is a variant-type node that is meant to be used as a part
/// of a tree data structure. As all Scheme programs are in the form of
/// trees due to the expression-only nature of the grammar and semantics
/// of the language, it is easy to idealize the organization of data as a
/// tree.
///
/// As it is the core data class for the project, it is also the primary
/// interface for data exchange within the program, along with DataDataNode.


/// @brief The DataNode structure implementation for the project.
///
/// Requires `std::enable_shared_from_this<T>` in order to transmit
/// parent node shared pointer to the child. 
template <typename T>
struct DataNode : public IDataNode<T> {

    /// @brief Contructor forwards arguments to internal data
    template <typename... Args>
    DataNode(Args... args) :
        data(std::make_shared<T>(std::forward<Args>(args)...)) {}

    virtual ~DataNode() {}


    /// @brief Returns a shared_ptr to the parent if it exists.
    ///        Otherwise, it's just a nullptr.
    virtual std::shared_ptr<IDataNode<T>> get_parent() {
        // If we can get the parent from the weak pointer,
        // then return it.

        // Otherwise, return a nullptr.
        if (auto ptr = this->parent.lock()) {
            return ptr;
        } else {
            /// @todo Decide on whether we should return nullptr or
            /// throw an exception.
            return nullptr;
        }
    }

    /// @brief Sets the parent node pointer to another one.
    virtual void set_parent(std::shared_ptr<IDataNode<T>> node) {
        this->parent = node; 
    }

    /// @brief Inserts a pointer to child in the internal vector<ptr>
    virtual std::shared_ptr<IDataNode<T>> insert_child(
        int                             index,
        std::shared_ptr<IDataNode<T>>   node
    ) {
        try {
            return *(this->children.insert(
                        this->children.begin() + valid_index(index),
                        node
                   ));
        } catch (std::runtime_error& e) {
            return nullptr;
        }
    }

    /// @brief Removes a child by 0-based index.
    ///
    /// If the index is out of bounds, it will return `nullptr`.
    virtual std::shared_ptr<IDataNode<T>> remove_child(int index) {
        try {
            /// @note vector::erase returns the iterator to the next element
            ///       after the deleted one. So if the vector is empty,
            ///       it becomes invalid to dereference it.
            (this->children.erase(this->children.begin() + valid_index(index)));

            /// @todo Refactor interface for remove_child so that it return void.
            return nullptr;
        } catch (std::runtime_error& e) {
            return nullptr;
        }
    }

    /// @brief Pushs a child onto the vector of children using `push_back()`
    virtual std::shared_ptr<IDataNode<T>> push_child(T node) {
        this->children.push_back(std::make_shared<DataNode<T>>(node));

        // Set the parent of the last child as this node.
        // We store `last_child` to avoid executing `this->get_last_child()`
        // twice.
        auto last_child = this->get_last_child();
        // @note `this->shared_from_this()` requires an explicit `this`
        //       in order for it to work corrrectly.
        last_child->set_parent(
            this->shared_from_this()
        );

        return last_child;
    }

    /// @brief Tries to get a child at the index.
    virtual std::shared_ptr<IDataNode<T>> get_child(int index) {
        try {
            return this->children[valid_index(index)];
        } catch (std::runtime_error& e) {
            return nullptr;
        }
    }

    /// @brief Returns the child at the end of the list.
    ///
    /// If there are no children, returns `nullptr`.
    virtual std::shared_ptr<IDataNode<T>> get_last_child() {
        if (this->children.size() > 0) {
            return this->children[this->children.size() - 1];
        } else {
            return nullptr;
        }
    }
    
    /// @brief Returns the number of direct children of the current tree.
    virtual std::size_t get_num_children() {
        return this->children.size();
    }

    /// @brief Gets the internal node.
    virtual std::shared_ptr<T> get_data() {
        return this->data;
    }

    /// @brief Sets the internal node pointer to the argument.
    virtual std::shared_ptr<T> set_data(T data) {
        *this->data = data;
        return this->data;
    }

private:
    /// @brief Checks for a valid index for the children vector.
    ///
    /// If it detects a problem, an exception will be thrown.
    size_t valid_index(int index) {
        if (index >= 0) {
            const size_t pos_index = static_cast<size_t>(index);

            if (pos_index < this->children.size()) {
                return pos_index;
            } else {
                throw std::runtime_error("DataNode<T>: Index is invalid (out of bounds).");
                return std::numeric_limits<size_t>::max();
            }
        } else {
            throw std::runtime_error("DataNode<T>: Index is invalid (negative).");
            return std::numeric_limits<size_t>::max();
        }
    }


    /// The key tag by which **Disjointness of Types** (R7RS, Sect. 3.2)
    /// will be implemented with and be kept updated with.
    MetaTag type_tag;

    /// The internal variant data type that will contain
    /// a reference to one of the contained data types.
    std::shared_ptr<T>    data;

    std::vector<std::shared_ptr<IDataNode<T>>>   children;
    std::weak_ptr<IDataNode<T>>                  parent;    
};

// #include <map>
// 
// struct Environment {
//     std::map<std::string, DataNode> symbol_table;
// };

} // namespace shaka

#endif // SHAKA_DATANODE_H
