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

    ASTNode() :
        data(MetaTag::NULL_LIST) {}

    ASTNode(MetaTag metatag) :
        data(metatag) {}

    ASTNode(int i) :
        data(i) {}
    
    ASTNode(std::string str) :
        data(str) {}

    ASTNode(std::shared_ptr<ASTNode>&& node) :
        data(std::move(node->data)) {}

    template <typename T>
    std::shared_ptr<ASTNode> insert(T data) {

        // Checks whether T is within the bounded variant types.
        static_assert(
            boost::mpl::contains<Data::types, T>::type::value,
            "T is not within the bounded types of the internal data variant."
        );


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

    template <typename T>
    std::shared_ptr<ASTNode> insert(std::shared_ptr<T> node) {

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


    void remove(int index) {
        if (index < 0 || index >= children.size()) {
            throw std::out_of_range("ASTNode.remove: index is out of range.");
        } else {
            children.erase(children.begin() + index);
        }
    }

    std::shared_ptr<ASTNode> get_node(int index) {
        if (index < 0 || index >= children.size()) {
            throw std::out_of_range("ASTNode.get_node: index is out of range.");
        } else {
            return children[index];
        }
    }

    void visit(std::function<void(ASTNode*)> f) {
        f(this);
    }

    Data& get_data() {
        return this->data;
    }

    std::vector<std::shared_ptr<ASTNode>>& get_children() {
        return this->children;
    }

private:
    Data                                    data;  
    std::vector<std::shared_ptr<ASTNode>>   children;
};

#endif // ASTNODE_H