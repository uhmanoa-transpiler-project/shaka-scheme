#include <gtest/gtest.h>

#include "core/base/Core.h"
// #include "core/base/Define.h"

#include <sstream>

using namespace shaka;

TEST(Define,  simple_define) {
    
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
        DataNode(Number(2))
    ));
    std::cout << *define << std::endl;
    std::cout<<*define->cdr()<<std::endl;
    //  constructing evaluator 
        Evaluator evaluator(
            define->cdr(), env
        );
        evaluator.evaluate(shaka::eval::Define());
        env->print_bindings(std::cout);

}

TEST(Define,  less_simple_define) {
    
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

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}