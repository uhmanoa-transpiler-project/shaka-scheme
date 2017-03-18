#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "Data.h"
#include "DataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Define.h"
#include "Procedure.h"

#include "Eval_Define_impl.h"
#include "Eval_Variable_impl.h"
#include "Eval_PrintTree.h"

using Data = shaka::Data;

using IDataTree = shaka::IDataNode<Data>;
using DataTree = shaka::DataNode<Data>;

using Environment =
    shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;


TEST(Evaluator_define, define_symbol_number) {
    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::DEFINE);

    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);
    // Pushed the symbol
    root->push_child(shaka::Symbol("a"));
    // Pushed a value
    root->push_child(shaka::Number(1));

    ASSERT_EQ(root->get_num_children(), 2);

    // /* constructing evaluator */
    shaka::Evaluator evaluator(
        root,
        env
    );

    // Evaluate the next thing using the Define strategy.
    evaluator.evaluate(shaka::eval::Define());

    for (auto it : env->get_keys()) {
        std::cout << it.get_value() << std::endl;
    }

    ASSERT_EQ(root->get_num_children(), 2);

    ASSERT_EQ(typeid(shaka::Number), env->get_value(shaka::Symbol("a"))->get_data()->type());

    ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*env->get_value(shaka::Symbol("a"))->get_data()));
}

TEST(Evaluator_define, define_symbol_list) {
    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::DEFINE);

    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    // Pushed the symbol
    root->push_child(shaka::Symbol("a"));

    // Pushed a literal list of values.
    auto list_node = root->push_child(shaka::MetaTag::LIST);
    list_node->push_child(shaka::Number(1));
    list_node->push_child(shaka::Number(2));
    list_node->push_child(shaka::Number(3));

    // /* constructing evaluator */
    shaka::Evaluator evaluator(
        root,
        env
    );

    evaluator.evaluate(shaka::eval::PrintTree<std::cout>());
    // Evaluate the next thing using the Define strategy.
    evaluator.evaluate(shaka::eval::Define());

    ASSERT_EQ(typeid(shaka::MetaTag), env->get_value(shaka::Symbol("a"))->get_data()->type());

    ASSERT_EQ(shaka::MetaTag::LIST, shaka::get<shaka::MetaTag>(*env->get_value(shaka::Symbol("a"))->get_data()));
    ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*env->get_value(shaka::Symbol("a"))->get_child(0)->get_data()));
    ASSERT_EQ(shaka::Number(2), shaka::get<shaka::Number>(*env->get_value(shaka::Symbol("a"))->get_child(1)->get_data()));
    ASSERT_EQ(shaka::Number(3), shaka::get<shaka::Number>(*env->get_value(shaka::Symbol("a"))->get_child(2)->get_data()));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
