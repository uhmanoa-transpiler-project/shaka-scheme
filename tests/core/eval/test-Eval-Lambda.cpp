#include <gtest/gtest.h>

#include "core/base/Core.h"
#include "core/eval/Lambda_impl.h"

#include <sstream>

using namespace shaka;

TEST(Lambda, initialization) {
    // (lambda (x)  1)

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
    // (lambda (x y) 1)

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
    // (lambda () 1)

    //create the environment
    EnvPtr env = std::make_shared<Environment>(nullptr);


    NodePtr lambda = std::make_shared<DataNode>(DataNode::list(
        DataNode(Symbol("lambda")),
        DataNode::list(),
        DataNode(Number(1))
    ));

    std::cout << *lambda<< std::endl;
    //  constructing evaluator 
    Evaluator evaluator(
        lambda->cdr(), env
    );
    Procedure procedure = get<Procedure>(evaluator.evaluate(
    shaka::eval::Lambda())->get_data());
    std::size_t arity= procedure.get_fixed_arity();
    bool varity= procedure.is_variable_arity();
    std::size_t size= 0;
    ASSERT_EQ(size, arity);
    ASSERT_EQ(false , varity);
}

TEST(Lambda, var_arity){
    // (lambda ( a b . c) 1)
    DataNode body = DataNode(Number(1));
    EnvPtr env = std::make_shared<Environment>(nullptr);
    
    DataNode a = DataNode::cons(DataNode(Symbol("b")),DataNode(Symbol("c")));
    DataNode args = DataNode::cons(DataNode(Symbol("a")), a);

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
    std::size_t arity= procedure.get_fixed_arity();
    bool varity= procedure.is_variable_arity();
    std::size_t size= 2;
    ASSERT_EQ(size, arity);
    ASSERT_EQ(true , varity);
}

TEST(Lambda, single_arity){
    // (lambda x x)
    DataNode body = DataNode::list(Number(1));
    EnvPtr env = std::make_shared<Environment>(nullptr);


    NodePtr lambda = std::make_shared<DataNode>(DataNode::list(
        DataNode(Symbol("lambda")),
        DataNode(Symbol("x")),
        DataNode(Symbol("x"))
        ));
    std::cout << *lambda << std::endl;
    //  constructing evaluator 
    Evaluator evaluator(
        lambda->cdr(), env
    );
    Procedure procedure = get<Procedure>(evaluator.evaluate(
    shaka::eval::Lambda())->get_data());
    std::size_t arity= procedure.get_fixed_arity();
    bool varity= procedure.is_variable_arity();
    std::size_t size= 0;
    ASSERT_EQ(size, arity);
    ASSERT_EQ(true , varity);
}

TEST(Lambda, define){
    
    DataNode body = DataNode::list(Number(1));
    EnvPtr env = std::make_shared<Environment>(nullptr);


    NodePtr lambda = std::make_shared<DataNode>(DataNode::list(
        DataNode(Symbol("lambda")),
        DataNode::list(DataNode(Symbol("x"))),
        DataNode(Symbol("x"))
        ));
    NodePtr define = std::make_shared<DataNode>(DataNode::list(
        DataNode(Symbol("define")),
        DataNode(Symbol("a")),
        lambda
    ));
    std::cout << *define << std::endl;
    std::cout<<*define->cdr()<<std::endl;
    //  constructing evaluator 
        Evaluator evaluator(
            define->cdr(), env
        );
        evaluator.evaluate(shaka::eval::Define());
        env->print_bindings(std::cout);
//     Procedure procedure = get<Procedure>(evaluator.evaluate(
//     shaka::eval::Lambda())->get_data());
//     std::size_t arity= procedure.get_fixed_arity();
//     bool varity= procedure.is_variable_arity();
//     std::size_t size= 0;
//     ASSERT_EQ(size, arity);
//     ASSERT_EQ(true , varity);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}