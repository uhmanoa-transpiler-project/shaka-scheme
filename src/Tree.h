#ifndef SHAKA_TREE_H
#define SHAKA_TREE_H

#include <vector>

#include "ITree.h"

/*
namespace shaka {

/// @brief A basic implementation of the `ITree` interface.
template <typename T>
struct Tree : public ITree<T> {
    virtual ~Tree() {}

    /// @brief Forwards argument to the T constructor
    template <typename... Args>
    Tree(Args&&... args) :
        node(std::make_shared<T>(std::forward<Args&&...>(args)...)) {}

    /// @brief Returns a shared_ptr to the parent if it exists.
    ///        Otherwise, it's just a nullptr.
    virtual std::shared_ptr<ITree<T>> get_parent() {
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

    /// @brief Inserts a pointer to child in the internal vector<ptr>
    virtual std::shared_ptr<ITree<T>> insert_child(
        int                         index,
        std::shared_ptr<ITree<T>>   node
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
    virtual std::shared_ptr<ITree<T>> remove_child(int index) {
        try {
            return *(this->children.erase(this->children.begin() + valid_index(index)));
        } catch (std::runtime_error& e) {
            return nullptr;
        }
    }

    /// @brief Pushs a child onto the vector of children using `push_back()`
    virtual std::shared_ptr<ITree<T>> push_child(T node) {
        this->children.push_back(std::make_shared<Tree<T>>(node));
        return this->children[this->children.size() - 1];
    }

    /// @brief Tries to get a child at the index.
    virtual std::shared_ptr<ITree<T>> get_child(int index) {
        try {
            return this->children[valid_index(index)];
        } catch (std::runtime_error& e) {
            return nullptr;
        }
    }

    /// @brief Returns the child at the end of the list.
    ///
    /// If there are no children, returns `nullptr`.
    virtual std::shared_ptr<ITree<T>> get_last_child() {
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
    virtual std::shared_ptr<T>        get_node() {
        return this->node;
    }

    /// @brief Sets the internal node pointer to the argument.
    virtual std::shared_ptr<T>        set_node(T node) {
        *this->node = node;
        return this->node;
    }

    std::vector<std::shared_ptr<ITree<T>>>   children;
    std::weak_ptr<ITree<T>>                  parent;    
    std::shared_ptr<T>                       node;

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
                throw std::runtime_error("Tree<T>: Index is invalid (out of bounds).");
                return std::numeric_limits<size_t>::max();
            }
        } else {
            throw std::runtime_error("Tree<T>: Index is invalid (negative).");
            return std::numeric_limits<size_t>::max();
        }
    }
};

} // namespace shaka
*/


#endif // SHAKA_TREE_H
