#include <gtest/gtest.h>
#include "macro/Macro.h"
#include "Eval_Macro_Substitute_impl.h"
#include "Environment.h"

TEST(Eval_Macro_Substitute, eval_macro_substitute) {
    using namespace shaka::macro;
    using INodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    using NodePtr = std::shared_ptr<shaka::DataNode<shaka::Data>>;
    using Node = shaka::DataNode<shaka::Data>;

    // Creating a (let1 (a 1) a) tree
    auto root = std::make_shared<Node>(shaka::MetaTag::PROC_CALL);
        root->push_child(shaka::Symbol("let1"));
        auto binding_list = root->push_child(shaka::MetaTag::LIST);
            auto binding0 = binding_list->push_child(shaka::MetaTag::LIST);
                binding0->push_child(shaka::Symbol("a"));
                binding0->push_child(shaka::Number(1));
            binding_list->push_child(shaka::Symbol("a"));

    // Creating a single (let1 (name expr) do_expr) arguments pattern tree.
    auto pat_root = std::make_shared<Node>(shaka::MetaTag::LIST);
        auto pat_binding_list = pat_root->push_child(shaka::MetaTag::LIST);
            pat_binding_list->push_child(shaka::Symbol("name"));
            pat_binding_list->push_child(shaka::Symbol("expr"));
        pat_root->push_child(shaka::Symbol("do_expr"));

    std::cout << "pat_root: " << std::endl;
    shaka::Evaluator eval2(pat_root, nullptr);
    eval2.evaluate(shaka::eval::PrintTree<std::cout>());


    // Create the pattern.
    Pattern p(pat_root);

    // Assert that the match is correct for the elipsis,
    // but that it is wrong for the ellipses, 1 argument pattern.
    ASSERT_TRUE(p.matches(root));

    auto env = std::make_shared<shaka::Environment<shaka::Symbol, INodePtr>>(nullptr);
    auto bindings = p.get_bindings();
    auto keys = bindings->get_keys();

    for (auto it : keys) {
        shaka::Evaluator eval(bindings->get_value(it), env);
        std::cout << "|" << it.get_value() << "|:" << std::endl;
        eval.evaluate(shaka::eval::PrintTree<std::cout>());
        env->set_value(it, bindings->get_value(it));
    }

    auto template2_root = std::make_shared<Node>(shaka::MetaTag::PROC_CALL);
        auto template2_lambda = template2_root->push_child(shaka::MetaTag::LAMBDA);
            auto template2_argslist = template2_lambda->push_child(shaka::MetaTag::LIST);
                template2_argslist->push_child(shaka::Symbol("name"));
            auto template2_body = template2_lambda->push_child(shaka::MetaTag::LIST);
                template2_body->push_child(shaka::Symbol("expr"));
        auto template2_args = template2_root->push_child(shaka::MetaTag::LIST);
            template2_args->push_child(shaka::Symbol("do_expr"));

    shaka::Evaluator substitutor(template2_root, bindings);
    auto result = substitutor.evaluate(shaka::eval::Macro_Substitute());

    shaka::Evaluator(result, nullptr).evaluate(shaka::eval::PrintTree<std::cout>());

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
