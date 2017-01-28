#ifndef SHAKA_TREE_H
#define SHAKA_TREE_H

#include <vector>

#include "ITree.h"

/// @brief A basic implementation of the `ITree` interface.
template <typename T>
struct Tree : public ITree<T> {
    virtual ~Tree() {}

    template <typename... Args>
    Tree(Args&&... args) :
        data(std::make_shared<T>(std::forward<Args&&...>(args)...)) {}

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

    virtual std::shared_ptr<ITree<T>> remove_child(int index) {
        try {
            return *(this->children.erase(this->children.begin() + valid_index(index)));
        } catch (std::runtime_error& e) {
            return nullptr;
        }
    }

    virtual std::shared_ptr<ITree<T>> push_child(T data) {
        this->children.push_back(std::make_shared<Tree<T>>(data));
        return this->children[this->children.size() - 1];
    }

    virtual std::shared_ptr<ITree<T>> get_child(int index) {
        try {
            return this->children[valid_index(index)];
        } catch (std::runtime_error& e) {
            return nullptr;
        }
    }

    virtual std::shared_ptr<ITree<T>> get_last_child() {
        if (this->children.size() > 0) {
            return this->children[this->children.size() - 1];
        } else {
            return nullptr;
        }
    }

    virtual std::shared_ptr<T>        get_data() {
        return this->data;
    }

    virtual std::shared_ptr<T>        set_data(T data) {
        *this->data = data;
        return this->data;
    }

    std::vector<std::shared_ptr<ITree<T>>>   children;
    std::weak_ptr<ITree<T>>                  parent;    
    std::shared_ptr<T>                       data;

private:
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


#endif // SHAKA_TREE_H
