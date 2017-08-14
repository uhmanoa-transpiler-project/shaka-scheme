#include <gtest/gtest.h>
#include "core/base/Core.h"
#include "core/eval/Eval.h"

using namespace shaka;

TEST(Eval_Lambda, evaluator_strategy) {
    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            DataNode::list(
                Symbol("x")
            ),
            Symbol("x")
        ));
        auto env = std::make_shared<Environment>(nullptr);
        Evaluator setup(nullptr, env);
        setup.evaluate(eval::SetupTopLevel());

        Evaluator eval(expr, env);
        auto val = eval.evaluate(eval::Lambda());
        std::cout << *val << std::endl;

        auto func_call = make_node(DataNode::list(
            *val,
            DataNode::list(
                Symbol("+"),
                Number(1),
                Number(1)
            )
        ));
        auto f = get<Procedure>(val->get_data());
        f.print_body(std::cout); std::cout << std::endl;
        Evaluator func_eval(func_call, env);
        auto result = func_eval.evaluate(eval::Expression());

        std::cout << *result << std::endl;

    }
}

TEST(Eval_Lambda, expression) {
    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            DataNode::list(
                Symbol("lambda"),
                DataNode::list(
                    Symbol("x")
                ),
                Symbol("x")
            ),
            DataNode::list(
                Symbol("-"),
                Number(1, 2),
                Number(1, 2)
            )
        ));
        auto env = std::make_shared<Environment>(nullptr);
        Evaluator setup(nullptr, env);
        setup.evaluate(eval::SetupTopLevel());

        Evaluator eval(expr, env);
        auto val = eval.evaluate(eval::Expression());
        std::cout << *val << std::endl;

    }
}
    
    /*
    {
        auto expr = std::make_shared<DataNode>(DataNode::list(
            Symbol("\\asdf"),
            Number(2)
        ));
        auto env = std::make_shared<Environment>(nullptr);
        Evaluator setup(nullptr, env);
        setup.evaluate(eval::SetupTopLevel());

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
        Evaluator setup(nullptr, env);
        setup.evaluate(eval::SetupTopLevel());

        Evaluator eval(expr, env);
        ASSERT_EQ(nullptr, eval.evaluate(eval::Define()));

        auto val = env->get_value(Symbol("asd.1"));
        std::cout << "val: " <<  *val << std::endl;
        ASSERT_TRUE(val->is_list());
        ASSERT_EQ(3, val->length());
        
        ASSERT_EQ(val->car()->get_data(), Data(Number(1)));
        ASSERT_EQ(val->cdr()->car()->get_data(), Data(Number(2)));
        ASSERT_EQ(val->cdr()->cdr()->car()->get_data(), Data(Number(3)));
    }
    */


/*
TEST(Eval_Define, shadow_keyword_define) {
    auto expr = make_node(DataNode::list(
        Symbol("define"),
        Symbol("define"),
        Number(1)
    ));
    auto env = std::make_shared<Environment>(nullptr);
    Evaluator setup(nullptr, env);
    setup.evaluate(eval::SetupTopLevel());

    auto before = env->get_value(Symbol("define"));
    ASSERT_TRUE(before->is_primitive_procedure());

    Evaluator eval(expr, env);
    ASSERT_EQ(nullptr, eval.evaluate(eval::Expression()));

    auto after = env->get_value(Symbol("define"));
    std::cout << *after << std::endl;
    ASSERT_TRUE(after->is_number());

    ASSERT_THROW({
        eval.evaluate(eval::Expression());
    }, std::runtime_error);
}
*/

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
