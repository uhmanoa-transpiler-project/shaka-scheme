#include <gtest/gtest.h>
#include "macro/Macro.h"
#include "Environment.h"

TEST(Macro_Pattern, let_tree_initialization) {
    using namespace shaka::macro;
    using INodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    using NodePtr = std::shared_ptr<shaka::DataNode<shaka::Data>>;
    using Node = shaka::DataNode<shaka::Data>;

    // Creating a (and 0 1 2) tree
    auto root = std::make_shared<Node>(shaka::MetaTag::PROC_CALL);
        root->push_child(shaka::Symbol("and"));
        auto args = root->push_child(shaka::MetaTag::LIST);
            args->push_child(shaka::Number(0));
            args->push_child(shaka::Number(1));
            args->push_child(shaka::Number(2));

    // Verify that the root of the tree is "and"
    ASSERT_EQ(shaka::Symbol("and"), shaka::get<shaka::Symbol>(*root->get_child(0)->get_data()));

    // Verify that the macro arguments list was setup correctly.
    ASSERT_EQ(shaka::MetaTag::LIST, shaka::get<shaka::MetaTag>(*root->get_child(1)->get_data()));
    ASSERT_EQ(root->get_child(1).get(), args.get());
    ASSERT_EQ(shaka::Number(0), shaka::get<shaka::Number>(*args->get_child(0)->get_data()));
    ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*args->get_child(1)->get_data()));
    ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*args->get_child(2)->get_data()));
}

TEST(Macro_Pattern, pattern_initialization) {
    using namespace shaka::macro;
    using INodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    using NodePtr = std::shared_ptr<shaka::DataNode<shaka::Data>>;
    using Node = shaka::DataNode<shaka::Data>;

    // Creating a (and 0) tree
    auto root = std::make_shared<Node>(shaka::MetaTag::PROC_CALL);
        root->push_child(shaka::Symbol("and"));
        auto args = root->push_child(shaka::MetaTag::LIST);
            args->push_child(shaka::Number(0));

    // Creating a single (and a) arguments pattern tree.
    auto pat_root = std::make_shared<Node>(shaka::MetaTag::LIST);
        pat_root->push_child(shaka::Symbol("a"));

    // Create the pattern.
    Pattern p(pat_root);

    // Match the pattern to the procedure call.
    ASSERT_TRUE(p.matches(root));
}

TEST(Macro_Pattern, test_pattern_mismatch) {
    using namespace shaka::macro;
    using INodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    using NodePtr = std::shared_ptr<shaka::DataNode<shaka::Data>>;
    using Node = shaka::DataNode<shaka::Data>;

    // Creating a (and 0 1 2) tree
    auto root = std::make_shared<Node>(shaka::MetaTag::PROC_CALL);
        root->push_child(shaka::Symbol("and"));
        auto args = root->push_child(shaka::MetaTag::LIST);
            args->push_child(shaka::Number(0));
            args->push_child(shaka::Number(1));
            args->push_child(shaka::Number(2));

    // Creating a single (and a) arguments pattern tree.
    auto pat_root = std::make_shared<Node>(shaka::MetaTag::LIST);
        pat_root->push_child(shaka::Symbol("a"));

    // Create the pattern.
    Pattern p(pat_root);

    // Match the pattern to the procedure call.
    ASSERT_FALSE(p.matches(root));
}

TEST(Macro_Pattern, test_elipsis) {
    using namespace shaka::macro;
    using INodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    using NodePtr = std::shared_ptr<shaka::DataNode<shaka::Data>>;
    using Node = shaka::DataNode<shaka::Data>;

    // Creating a (and 0 1 2) tree
    auto root = std::make_shared<Node>(shaka::MetaTag::PROC_CALL);
        root->push_child(shaka::Symbol("and"));
        auto args = root->push_child(shaka::MetaTag::LIST);
            args->push_child(shaka::Number(0));
            args->push_child(shaka::Number(1));
            args->push_child(shaka::Number(2));

    // Creating a single (and a) arguments pattern tree.
    auto pat_root = std::make_shared<Node>(shaka::MetaTag::LIST);
        pat_root->push_child(shaka::Symbol("a"));

    // Create the pattern.
    Pattern p(pat_root);

    // Create a pattern with elipses:
    // (and a b ...)
    auto pat2_root = std::make_shared<Node>(shaka::MetaTag::LIST);
        pat2_root->push_child(shaka::Symbol("a"));
        pat2_root->push_child(shaka::Symbol("b"));
        pat2_root->push_child(shaka::Symbol("..."));

    // Initialize the pattern.
    Pattern p2(pat2_root);

    // Assert that the match is correct for the elipsis,
    // but that it is wrong for the ellipses, 1 argument pattern.
    ASSERT_FALSE(p.matches(root));
    ASSERT_TRUE(p2.matches(root));

    auto env = std::make_shared<shaka::Environment<shaka::Symbol, INodePtr>>(nullptr);
    auto bindings = p2.get_bindings();

    for (auto it : bindings) {
        shaka::Evaluator eval(it.second, env);
        std::cout << "|" << it.first.get_value() << "|:" << std::endl;
        eval.evaluate(shaka::eval::PrintTree<std::cout>());
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
