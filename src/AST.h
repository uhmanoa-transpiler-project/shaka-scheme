#ifndef ASTNODE_H
#define ASTNODE_H

#include "precomp-boost.h"

#include <type_traits>

enum class MetaTag : int {
    NULL_LIST = 0,
    LIST,
    PROCEDURE,
    IF,
    ATOM
};

using Data = boost::variant<
    int,
    std::string,
    MetaTag
>;


// We need to inherit from std::enable_shared_from_this
// so that we can return a std::shared_ptr<ASTNode> to this
// for the visitor algorithms.
// Although this is sort of dangerous, this is also
class ASTNode {
public:

    // Default constructor
    ASTNode() :
        data(MetaTag::NULL_LIST) {}

    // MetaTag constructor
    ASTNode(MetaTag metatag) :
        data(metatag) {}

    // Number constructor
    ASTNode(int i) :
        data(i) {}

    // String constructor
    ASTNode(std::string str) :
        data(str) {}

    // Move constructor
    ASTNode(std::shared_ptr<ASTNode>&& node) :
        data(std::move(node->data)) {}

    // Inserts a child node, only if this node is a List.
    template <typename T>
    std::shared_ptr<ASTNode> push_child(T data) {

        // Checks whether T is within the bounded variant types.
        static_assert(
            boost::mpl::contains<Data::types, T>::type::value,
            "T is not within the bounded types of the internal data variant."
        );

        // Insert only if a list.
        if (MetaTag* p = boost::get<MetaTag>(&(this->data))) {
            if (*p == MetaTag::LIST) {
                children.push_back(std::make_shared<ASTNode>(data));
                return children[children.size()-1];
            } else {
                throw std::runtime_error(
                    "ASTNode.insert(T): this node is not a list!"
                );
            }

        } else {
            throw std::runtime_error(
                "ASTNode.insert(T): this node is not a MetaTag (or list)."
            );
        }
    }

    // Insert, but with the shared_ptr overload.
    template <typename T>
    std::shared_ptr<ASTNode> push_child(std::shared_ptr<T> node) {

        // Checks whether T is actually in the variant bounded types.
        static_assert(
            boost::mpl::contains<Data::types, T>::type::value,
            "T is not within the bounded types of the internal data variant."
        );

        if (MetaTag* p = boost::get<MetaTag>(&(this->data))) {
            if (*p == MetaTag::LIST) {
                children.push_back(std::make_shared(*node));
                return children[children.size()-1];
            } else {
                throw std::runtime_error(
                    "ASTNode.insert(node): Subject node is not a list!"
                );
            }

        } else {
            throw std::runtime_error(
                "ASTNode.insert(node): Subject node is not a MetaTag (or list)."
            );
        }
    }


    // Remove a child.
    void remove_child(int index) {
        if (index < 0 || index >= children.size()) {
            throw std::out_of_range("ASTNode.remove: index is out of range.");
        } else {
            children.erase(children.begin() + index);
        }
    }

    // Gets a child node.
    std::shared_ptr<ASTNode> get_child(int index) {
        if (index < 0 || index >= children.size()) {
            throw std::out_of_range("ASTNode.get_node: index is out of range.");
        } else {
            return children[index];
        }
    }

    // Applies a function to this node.
    void visit(std::function<void(ASTNode*)> f) {
        f(this);
    }

    // Get the internally stored data.
    Data& get_data() {
        return this->data;
    }

    // Gets the children.
    std::vector<std::shared_ptr<ASTNode>>& get_children() {
        return this->children;
    }

private:
    Data                                    data;  
    std::vector<std::shared_ptr<ASTNode>>   children;
};

#endif // ASTNODE_H