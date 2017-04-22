#include <gtest/gtest.h>
#include "core/base/Core.h"
#include "core/eval/Eval.h"

using namespace shaka;

TEST(Eval_Define, evaluator_strategy) {
    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Symbol("a"),
            Number(1)
        ));
        auto env = std::make_shared<Environment>(nullptr);

        Evaluator eval(expr, env);

        ASSERT_EQ(nullptr, eval.evaluate(eval::Define()));
        
        auto val = env->get_value(Symbol("a"));
        
        ASSERT_EQ(get<Number>(val->get_data()), Number(1));
    }

    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Symbol("\\asdf"),
            Number(2)
        ));
        auto env = std::make_shared<Environment>(nullptr);

        Evaluator eval(expr, env);
        ASSERT_EQ(nullptr, eval.evaluate(eval::Define()));

        auto val = env->get_value(Symbol("\\asdf"));
        
        ASSERT_EQ(get<Number>(val->get_data()), Number(2));
    }

    
    {
        auto expr = make_node(DataNode::list(
            Symbol("asd.1"),
            DataNode::list(
                Symbol("quote"),
                DataNode::list(
                    Number(1),
                    Number(2),
                    Number(3)
                )
            )
        ));
        auto env = std::make_shared<Environment>(nullptr);

        Evaluator eval(expr, env);
        ASSERT_EQ(nullptr, eval.evaluate(eval::Define()));

        auto val = env->get_value(Symbol("asd.1"));
        ASSERT_TRUE(val->is_list());
        ASSERT_EQ(3, val->length());
        
        ASSERT_EQ(val->car()->get_data(), Data(Number(1)));
        ASSERT_EQ(val->cdr()->car()->get_data(), Data(Number(2)));
        ASSERT_EQ(val->cdr()->cdr()->car()->get_data(), Data(Number(3)));
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
