
#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Expression.h"
#include "Procedure.h"

#include "Eval_Expression_impl.h"

using Data = shaka::Data;
using IDataTree = shaka::IDataNode<Data>;
using DataTree = shaka::DataNode<Data>;

using Environment =
    shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Evaluator_Expression, define_basic) {
    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::DEFINE);

    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);
    // Pushed the symbol
    root->push_child(shaka::Symbol("a"));
    // Pushed a value
    root->push_child(1);

    // /* constructing evaluator */
    shaka::Evaluator evaluator(
        root,
        env
    );

    // Evaluate the next thing using the Define strategy.
    evaluator.evaluate(shaka::eval::Expression());

    ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*env->get_value(shaka::Symbol("a"))->get_data()));
}

TEST(Evaluator_Expression, define_and_variable) {
    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::DEFINE);
    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);
    // Pushed the symbol
    root->push_child(shaka::Symbol("a"));
    // Pushed a value
    root->push_child(shaka::Number(1, 2));

    // /* constructing evaluator */
    shaka::Evaluator evaluator(
        root,
        env
    );

    // Evaluate the next thing using the Define strategy.
    evaluator.evaluate(shaka::eval::Expression());

    // Check that a == 1/2
    ASSERT_EQ(shaka::Number(1, 2), shaka::get<shaka::Number>(*env->get_value(shaka::Symbol("a"))->get_data()));

    // Create a second (define b a) expression.
    auto root2 = std::make_shared<DataTree>(shaka::MetaTag::DEFINE);
    root2->push_child(shaka::Symbol("b"));
    root2->push_child(shaka::Symbol("a"));

    // Evaluate the expression using the same environment as root1.
    shaka::Evaluator(root2, env).evaluate(shaka::eval::Expression());

    // check that b == a == 1/2
    ASSERT_EQ(shaka::Number(1, 2), shaka::get<shaka::Number>(*env->get_value(shaka::Symbol("b"))->get_data()));
    ASSERT_EQ(shaka::Number(1, 2), shaka::get<shaka::Number>(*env->get_value(shaka::Symbol("a"))->get_data()));

    // Extract the two shared_ptr to a and b in the Environment.
    auto node_a = shaka::Evaluator(
        std::make_shared<DataTree>(
            shaka::Symbol("a")
        ),
        env
    ).evaluate(shaka::eval::Expression());

    auto node_b = shaka::Evaluator(
        std::make_shared<DataTree>(
            shaka::Symbol("b")
        ),
        env
    ).evaluate(shaka::eval::Expression());

    // Check that the distinct locations of a and b are the same because they're numbers.
    EXPECT_EQ(node_a, node_b);
    ASSERT_EQ(
        shaka::get<shaka::Number>(*node_a->get_data()),
        shaka::get<shaka::Number>(*node_b->get_data())
    );
}

TEST(Evaluator_Expression, define_and_quote_and_variable) {
    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::DEFINE);
    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);
    // Pushed the symbol
    root->push_child(shaka::Symbol("a"));
    // Pushed a value
    root->push_child(shaka::Number(1, 2));

    // /* constructing evaluator */
    shaka::Evaluator evaluator(
        root,
        env
    );

    // Evaluate the next thing using the Define strategy.
    evaluator.evaluate(shaka::eval::Expression());

    // Check that a == 1/2
    ASSERT_EQ(shaka::Number(1, 2), shaka::get<shaka::Number>(*env->get_value(shaka::Symbol("a"))->get_data()));

    // Create a second (define b a) expression.
    auto root2 = std::make_shared<DataTree>(shaka::MetaTag::DEFINE);
    root2->push_child(shaka::Symbol("b"));
    auto root2_quotechild = root2->push_child(shaka::MetaTag::QUOTE);
    root2_quotechild->push_child(shaka::Symbol("a"));

    // Evaluate the expression using the same environment as root1.
    shaka::Evaluator(root2, env).evaluate(shaka::eval::Expression());

    // check that b == Symbol(a) and a == 1/2
    ASSERT_EQ(shaka::Symbol("a"), shaka::get<shaka::Symbol>(*env->get_value(shaka::Symbol("b"))->get_data()));
    ASSERT_EQ(shaka::Number(1, 2), shaka::get<shaka::Number>(*env->get_value(shaka::Symbol("a"))->get_data()));

    // Extract the two shared_ptr to a and b in the Environment.
    auto node_a = shaka::Evaluator(
        std::make_shared<DataTree>(
            shaka::Symbol("a")
        ),
        env
    ).evaluate(shaka::eval::Expression());

    auto node_b = shaka::Evaluator(
        std::make_shared<DataTree>(
            shaka::Symbol("b")
        ),
        env
    ).evaluate(shaka::eval::Expression());

    // Check that the distinct locations of a and b are the same because they're numbers.
    EXPECT_EQ(node_a, node_b);
    ASSERT_EQ(
        shaka::get<shaka::Number>(*node_a->get_data()),
        shaka::get<shaka::Number>(*node_b->get_data())
    );
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
