#include <gtest/gtest.h>

#include "core/base/Core.h"
#include "core/eval/Eval.h"

using namespace shaka;

TEST(Eval_If, evaluator_strategy) {
    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Boolean(true),
            Number(1)
        ));
        EnvPtr env = std::make_shared<Environment>(nullptr);
        Evaluator eval(expr, env);

        auto val = eval.evaluate(eval::If());

        ASSERT_EQ(get<Number>(val->get_data()), Number(1));
    }
    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Boolean(false),
            Number(2)
        ));
        EnvPtr env = std::make_shared<Environment>(nullptr);
        Evaluator eval(expr, env);

        auto val = eval.evaluate(eval::If());
        
        ASSERT_EQ(val, nullptr);
    }
    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Boolean(false),
            Number(2),
            Number(1, 2)
        ));
        EnvPtr env = std::make_shared<Environment>(nullptr);
        Evaluator eval(expr, env);

        auto val = eval.evaluate(eval::If());
        
        ASSERT_EQ(get<Number>(val->get_data()), Number(1, 2));
    }
}

TEST(Eval_If, expression) {
    auto expr = make_node(DataNode::list(
        Symbol("if"),
        Number(1),
        Number(2),
        Number(3)
    ));
    auto env = std::make_shared<Environment>(nullptr);
    Evaluator setup(nullptr, env);
    setup.evaluate(eval::SetupTopLevel());

    Evaluator eval(expr, env);
    auto val = eval.evaluate(eval::Expression());
    ASSERT_EQ(get<Number>(val->get_data()), Number(2));
}
/*
*/

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
