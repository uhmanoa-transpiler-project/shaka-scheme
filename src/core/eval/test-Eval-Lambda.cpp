#include <gtest/gtest.h>

#include "core/base/DataNode.h"
#include "core/base/Evaluator.h"
#include "core/eval/Lambda_impl.h"
#include "core/base/Procedure_impl.h"
#include "core/eval/ProcedureBody_impl.h"
#include <sstream>

using namespace shaka;

TEST(Lambda, initialization) {
    // (lambda (x) (1) )

    //create the environment
    EnvPtr env = std::make_shared<Environment>(nullptr);

    DataNode args = DataNode::list(DataNode(Symbol("x")));

    DataNode body = DataNode(Number(1));

    NodePtr lambda = std::make_shared<DataNode>(DataNode::list(
        DataNode(Symbol("lambda")),
        args, 
        body));
    std::cout << *lambda << std::endl;
    //  constructing evaluator 
    Evaluator evaluator(
        lambda->cdr(), env
    );
    shaka::Procedure procedure = shaka::get<shaka::Procedure>(evaluator.evaluate(
    shaka::eval::Lambda())->get_data());
    std::size_t arity= procedure.get_fixed_arity();
    bool varity= procedure.is_variable_arity();
    std::size_t size= 1;
    ASSERT_EQ(size, arity);
    ASSERT_EQ(false , varity);
}
TEST(Lambda, fixed_arity) {
    // (lambda (x y) (1) )

    //create the environment
    EnvPtr env = std::make_shared<Environment>(nullptr);

    DataNode arg1(Symbol("x"));
    DataNode arg2(Symbol("y"));
    DataNode args = DataNode::list(arg1, arg2);

    DataNode body = DataNode(Number(1));

    NodePtr lambda = std::make_shared<DataNode>(DataNode::list(
        DataNode(Symbol("lambda")),
        args, body));
    std::cout << *lambda << std::endl;
    //  constructing evaluator 
    Evaluator evaluator(
        lambda->cdr(), env
    );
    shaka::Procedure procedure = shaka::get<shaka::Procedure>(evaluator.evaluate(
    shaka::eval::Lambda())->get_data());
    std::size_t arity= procedure.get_fixed_arity();
    bool varity= procedure.is_variable_arity();
    std::size_t size= 2;
    ASSERT_EQ(size, arity);
    ASSERT_EQ(false , varity);
}

TEST(Lambda, no_arity) {
    // (lambda () (1) )

    //create the environment
    EnvPtr env = std::make_shared<Environment>(nullptr);
    DataNode args = DataNode::list();
    DataNode body = DataNode::list(Number(1));


    NodePtr lambda = std::make_shared<DataNode>(DataNode::list(
        DataNode(Symbol("lambda")),
        args, body));
    std::cout << *lambda << std::endl;
    //  constructing evaluator 
    Evaluator evaluator(
        lambda->cdr(), env
    );
    Procedure procedure = get<Procedure>(evaluator.evaluate(
    shaka::eval::Lambda())->get_data());
    std::cout<<"5"<<std::endl;
    std::size_t arity= procedure.get_fixed_arity();
    bool varity= procedure.is_variable_arity();
    std::size_t size= 0;
    ASSERT_EQ(size, arity);
    ASSERT_EQ(false , varity);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}