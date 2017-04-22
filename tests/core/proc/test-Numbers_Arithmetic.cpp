#include <gtest/gtest.h>
#include "core/base/Core.h"
#include "core/eval/Eval.h"

using namespace shaka;

TEST(Numbers_Arithmetic, add) {
    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Symbol("+"),
            Number(1),
            Number(1)
        ));
        auto env = std::make_shared<Environment>(nullptr);
        Evaluator setup(nullptr, env);
        setup.evaluate(eval::SetupTopLevel());

        Evaluator eval(expr, env);

        ASSERT_EQ(
            make_node(Number(2))->get_data(),
            eval.evaluate(eval::Expression())->get_data());
    }

    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Symbol("+"),
            Number(10234)
        ));
        auto env = std::make_shared<Environment>(nullptr);
        Evaluator setup(nullptr, env);
        setup.evaluate(eval::SetupTopLevel());

        Evaluator eval(expr, env);

        ASSERT_EQ(
            make_node(Number(10234))->get_data(),
            eval.evaluate(eval::Expression())->get_data());
    }

    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Symbol("+"),
            Number(10234),
            Number(-10234)
        ));
        auto env = std::make_shared<Environment>(nullptr);
        Evaluator setup(nullptr, env);
        setup.evaluate(eval::SetupTopLevel());

        Evaluator eval(expr, env);

        ASSERT_EQ(
            make_node(Number(0))->get_data(),
            eval.evaluate(eval::Expression())->get_data());
    }

    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Symbol("+"),
            Number(1, 2),
            Number(3, 2)
        ));
        auto env = std::make_shared<Environment>(nullptr);
        Evaluator setup(nullptr, env);
        setup.evaluate(eval::SetupTopLevel());

        Evaluator eval(expr, env);

        ASSERT_EQ(
            make_node(Number(4, 2))->get_data(),
            eval.evaluate(eval::Expression())->get_data());
    }

    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Symbol("+"),
            Number(1, 2),
            Number(1.0)
        ));
        auto env = std::make_shared<Environment>(nullptr);
        Evaluator setup(nullptr, env);
        setup.evaluate(eval::SetupTopLevel());

        Evaluator eval(expr, env);

        // Given the way that IEEE floating point is represented,
        // since it's base-2 for the mantissa,
        // 1/2 + 1.0 should be exactly 2^0 + 2^-1, or 1.5
        ASSERT_EQ(
            make_node(Number(1.5))->get_data(),
            eval.evaluate(eval::Expression())->get_data());
    }
}

TEST(Numbers_Arithmetic, sub) {
    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Symbol("-"),
            Number(1)
        ));
        auto env = std::make_shared<Environment>(nullptr);
        Evaluator setup(nullptr, env);
        setup.evaluate(eval::SetupTopLevel());

        Evaluator eval(expr, env);

        ASSERT_EQ(
            make_node(Number(-1))->get_data(),
            eval.evaluate(eval::Expression())->get_data());
    }

    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Symbol("-"),
            Number(1),
            Number(3)
        ));
        auto env = std::make_shared<Environment>(nullptr);
        Evaluator setup(nullptr, env);
        setup.evaluate(eval::SetupTopLevel());

        Evaluator eval(expr, env);

        ASSERT_EQ(
            make_node(Number(-2))->get_data(),
            eval.evaluate(eval::Expression())->get_data());
    }
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
