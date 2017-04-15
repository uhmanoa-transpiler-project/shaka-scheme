#include <gtest/gtest.h>
#include "core/base/DataNode.h"
#include "core/base/Evaluator.h"
#include "core/eval/Define_impl.h"
#include "core/eval/Variable_impl.h"
#include "core/eval/Quote_impl.h"

#include <sstream>

using namespace shaka;

auto define_eval = [](const NodePtr& list, const NodePtr& env_node) -> NodePtr {
    if (env_node->is_environment()) {
        auto env = get<EnvPtr>(env_node->get_data());
        shaka::Evaluator(list, env).evaluate(shaka::eval::Define());
        return nullptr;
    }
    else {
        throw std::runtime_error("define_eval: environment node does not hold an environment");
        return nullptr;
    }
};

auto variable_eval = [](const NodePtr& node, const NodePtr& env_node) -> NodePtr {
    if (env_node->is_environment()) {
        auto env = get<EnvPtr>(env_node->get_data());
        return shaka::Evaluator(node, env).evaluate(shaka::eval::Variable());
    }
    else {
        throw std::runtime_error("variable_eval: environment node does not hold an environment");
        return nullptr;
    }
};

auto quote_eval = [](const NodePtr& node, const NodePtr& env_node) -> NodePtr {
    if (env_node->is_environment()) {
        auto env = get<EnvPtr>(env_node->get_data());
        return shaka::Evaluator(node, env).evaluate(shaka::eval::Quote());
    }
    else {
        throw std::runtime_error("variable_eval: environment node does not hold an environment");
        return nullptr;
    }
};

TEST(Eval_mock, define) {
    auto l0 = std::make_shared<DataNode>(DataNode::list(
        Symbol("define"),
        Symbol("a"),
        Number(1)
    ));
    auto env = std::make_shared<DataNode>(std::make_shared<Environment>(nullptr));
    define_eval(l0, env);
    get<EnvPtr>(env->get_data())->print_bindings(std::cout);
}

TEST(Eval_mock, variable) {
    auto l0 = std::make_shared<DataNode>(DataNode::list(
        Symbol("define"),
        Symbol("a"),
        Number(1)
    ));
    auto l1 = std::make_shared<DataNode>(Symbol("a"));
    auto env = std::make_shared<DataNode>(std::make_shared<Environment>(nullptr));

    define_eval(l0, env);
    std::cout << *variable_eval(l1, env) << std::endl;
    get<EnvPtr>(env->get_data())->print_bindings(std::cout);
}

TEST(Eval_mock, quote) {
    auto l0 = std::make_shared<DataNode>(DataNode::list(
        Symbol("quote"),
        DataNode::list(
            Symbol("define"),
            Symbol("b"),
            Number(1, 2)
        )
    ));
    auto env = std::make_shared<DataNode>(std::make_shared<Environment>(nullptr));

    std::cout << *quote_eval(l0, env) << std::endl;
    get<EnvPtr>(env->get_data())->print_bindings(std::cout);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
