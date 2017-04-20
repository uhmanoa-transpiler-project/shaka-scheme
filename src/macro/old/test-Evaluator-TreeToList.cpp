#include <gtest/gtest.h>
#include "DataNode.h"
#include "Evaluator.h"
#include "Eval_PrintTree.h"
#include "Eval_TreeToList_impl.h"
#include "Procedure_impl.h"
#include "Environment.h"

TEST(Eval_TreeToList, define) {
    using INodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    using NodePtr = std::shared_ptr<shaka::DataNode<shaka::Data>>;
    using Node = shaka::DataNode<shaka::Data>;

    auto root = std::make_shared<Node>(shaka::MetaTag::LIST);
        auto define_root = root->push_child(shaka::MetaTag::DEFINE);
            define_root->push_child(shaka::Symbol("a"));
            define_root->push_child(shaka::Number(1));
        root->push_child(shaka::Number(2));

    // Rewrite the nodes in list-only format.
    shaka::Evaluator eval(root, nullptr);
    auto result = eval.evaluate(shaka::eval::TreeToList());

    // Print out the adjusted tree.
    shaka::Evaluator(result, nullptr).evaluate(shaka::eval::PrintTree<std::cout>());
}

TEST(Eval_TreeToList, lambda) {
    using INodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    using NodePtr = std::shared_ptr<shaka::DataNode<shaka::Data>>;
    using Node = shaka::DataNode<shaka::Data>;

    auto lambda_root = std::make_shared<Node>(shaka::MetaTag::LAMBDA);
        auto lambda_args = lambda_root->push_child(shaka::MetaTag::LIST);
            lambda_args->push_child(shaka::Symbol("a"));
            lambda_args->push_child(shaka::Symbol("b"));
        auto lambda_body = lambda_root->push_child(shaka::MetaTag::LIST);
            lambda_body->push_child(shaka::Symbol("a"));
            lambda_body->push_child(shaka::Number(1));

    // Rewrite the nodes in list-only format.
    shaka::Evaluator eval(lambda_root, nullptr);
    auto result = eval.evaluate(shaka::eval::TreeToList());

    // Print out the adjusted tree.
    shaka::Evaluator(result, nullptr).evaluate(shaka::eval::PrintTree<std::cout>());
}


TEST(Eval_TreeToList, if_node) {
    using INodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    using NodePtr = std::shared_ptr<shaka::DataNode<shaka::Data>>;
    using Node = shaka::DataNode<shaka::Data>;

    auto if_root = std::make_shared<Node>(shaka::MetaTag::IF);
            if_root->push_child(shaka::Symbol("a"));
            if_root->push_child(shaka::Symbol("asdf"));
            if_root->push_child(shaka::Number(1));

    // Rewrite the nodes in list-only format.
    shaka::Evaluator eval(if_root, nullptr);
    auto result = eval.evaluate(shaka::eval::TreeToList());

    // Print out the adjusted tree.
    shaka::Evaluator(result, nullptr).evaluate(shaka::eval::PrintTree<std::cout>());
}

TEST(Eval_TreeToList, proc_call) {
    using INodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    using NodePtr = std::shared_ptr<shaka::DataNode<shaka::Data>>;
    using Node = shaka::DataNode<shaka::Data>;

    auto proccall_root = std::make_shared<Node>(shaka::MetaTag::PROC_CALL);
            proccall_root->push_child(shaka::Symbol("a"));
            auto args = proccall_root->push_child(shaka::MetaTag::LIST);
                args->push_child(shaka::Symbol("asdf"));
                args->push_child(shaka::Number(1));

    // Rewrite the nodes in list-only format.
    shaka::Evaluator eval(proccall_root, nullptr);
    auto result = eval.evaluate(shaka::eval::TreeToList());

    // Print out the adjusted tree.
    shaka::Evaluator(result, nullptr).evaluate(shaka::eval::PrintTree<std::cout>());
}

TEST(Eval_TreeToList, quote) {
    using INodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    using NodePtr = std::shared_ptr<shaka::DataNode<shaka::Data>>;
    using Node = shaka::DataNode<shaka::Data>;

    auto quote_root = std::make_shared<Node>(shaka::MetaTag::QUOTE);
        quote_root->push_child(shaka::Number(1));

    // Rewrite the nodes in list-only format.
    shaka::Evaluator eval(quote_root, nullptr);
    auto result = eval.evaluate(shaka::eval::TreeToList());

    // Print out the adjusted tree.
    shaka::Evaluator(result, nullptr).evaluate(shaka::eval::PrintTree<std::cout>());
}




    // Creating a (and 0 1 2) tree
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
