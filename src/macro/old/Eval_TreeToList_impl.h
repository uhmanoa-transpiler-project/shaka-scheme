#ifndef SHAKA_EVAL_TREETOLIST_IMPL_H
#define SHAKA_EVAL_TREETOLIST_IMPL_H

#include "Eval_TreeToList.h"

namespace shaka {
namespace eval {

using T = shaka::Data;
using Key = shaka::Symbol;
using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
using Node = shaka::DataNode<shaka::Data>;

std::shared_ptr<IDataNode<T>> TreeToList::evaluate(
    std::shared_ptr<IDataNode<T>> node,
    std::shared_ptr<IEnvironment<Key, Value>> env
) {

    auto node_variant = *node->get_data();

    if (node_variant.type() == typeid(shaka::MetaTag)) {
        Value result = std::make_shared<Node>(shaka::MetaTag::LIST);
        auto tag = shaka::get<shaka::MetaTag>(node_variant);
        using namespace shaka;
        // If it's LIST, then make sure to rewrite the children nodes as lists
        // and then push onto the tree.
        if (tag == MetaTag::LIST) {
            for (std::size_t i = 0; i < node->get_num_children(); ++i) {
                this->evaluate(node->get_child(i), env)->copy_subtree_onto(result);
            }
        }
        // If it's DEFINE, rewrite as a list.
        else if (tag == MetaTag::DEFINE) {
            result->push_child(Symbol("define"));
            for (std::size_t i = 0; i < node->get_num_children(); ++i) {
                this->evaluate(node->get_child(i), env)->copy_subtree_onto(result);
            }
        }
        // If it's IF, evaluate its children as well.
        else if (tag == MetaTag::IF) {
            result->push_child(Symbol("if"));
            for (std::size_t i = 0; i < node->get_num_children(); ++i) {
                this->evaluate(node->get_child(i), env)->copy_subtree_onto(result);
            }
        }
        // If it's IF, evaluate its children as well.
        else if (tag == MetaTag::PROC_CALL) {
            // Transform the operator
            this->evaluate(node->get_child(0), env)->copy_subtree_onto(result);
            // Transform the operands
            auto body = node->get_child(1);
            for (std::size_t j = 0; j < body->get_num_children(); ++j) {
                this->evaluate(body->get_child(j), env)->copy_subtree_onto(result);
            }
        }
        // If it's LAMBDA, evaluate its children as well.
        else if (tag == MetaTag::LAMBDA) {
            result->push_child(Symbol("lambda"));
            // Transform the formals
            this->evaluate(node->get_child(0), env)->copy_subtree_onto(result);
            // Transform the body
            auto body = node->get_child(1);
            for (std::size_t j = 0; j < body->get_num_children(); ++j) {
                this->evaluate(body->get_child(j), env)->copy_subtree_onto(result);
            }
        }
        else if (tag == MetaTag::QUOTE) {
            result->push_child(Symbol("quote"));
            for (std::size_t i = 0; i < node->get_num_children(); ++i) {
                this->evaluate(node->get_child(i), env)->copy_subtree_onto(result);
            }
        }
        return result;
    } else {
        return node;
    }

}

std::shared_ptr<IDataNode<T>> ListToTree::evaluate(
    std::shared_ptr<IDataNode<T>> node,
    std::shared_ptr<IEnvironment<Key, Value>> env
) {
    auto node_variant = *node->get_data();

    // Check that the input node is a MetaTag
    if (node_variant.type() == typeid(shaka::MetaTag)) {
        auto tag = shaka::get<shaka::MetaTag>(node_variant);
        if (tag != shaka::MetaTag::LIST) {
            throw std::runtime_error("ListToTree: Cannot evaluate non-LIST");
            return nullptr;
        } 

        // If it's a null list, then just return it.
        if (node->get_num_children() == 0) { return node; }

        // Otherwise, we need to evaluate the first argument
        // and then decide if we can turn it into one of the
        // tree forms.

        // Evalaute the first argument.
        auto first = node->get_child(0);
    }

    return nullptr;

    

       
    // If the root is okay, then switch on the first symbol.
    

}

} // namespace eval
} // namespace shaka

#endif // SHAKA_EVAL_TREETRANSFORM_IMPL_H
