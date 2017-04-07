#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Lambda.h"
#include "Eval_Lambda_impl.h"

#include "Procedure.h"

using Data = shaka::Data;

using IDataTree = shaka::IDataNode<Data>;
using DataTree = shaka::DataNode<Data>;

using Environment =
    shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Evaluator_Lambda, initialization) {
    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LAMBDA);

    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);
    
    root->push_child(shaka::MetaTag::LIST);
    root->push_child(shaka::MetaTag::LIST);

    root->get_child(0)->push_child(shaka::Symbol("a"));
    root->get_child(1)->push_child(shaka::Number(1));

    //  constructing evaluator 
    shaka::Evaluator evaluator(
        root, env
    );
    shaka::Procedure procedure = shaka::get<shaka::Procedure>(*evaluator.evaluate(
    shaka::eval::Lambda())->get_data());
    std::size_t arity= procedure.get_fixed_arity();
    bool varity= procedure.is_variable_arity();
    std::size_t size= 1;
    ASSERT_EQ(size, arity);
    ASSERT_EQ(false, varity);
}

TEST(Evaluator_Lambda, lambda_define) {
    // (lambda () (define q 2))

    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LAMBDA);

    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);
    
    //arguments list
    auto args_root = root->push_child(shaka::MetaTag::LIST);
    //body of expressions
    auto body_root = root->push_child(shaka::MetaTag::LIST);

        // create define node
        auto define_root = body_root->push_child(shaka::MetaTag::DEFINE);
            define_root->push_child(shaka::Symbol("q"));
            define_root->push_child(shaka::Number(2));

        body_root->push_child(shaka::Symbol("q"));

    
   

    //  constructing evaluator 
    shaka::Evaluator evaluator(
        root, env
    );
    shaka::Procedure procedure = shaka::get<shaka::Procedure>(*evaluator.evaluate(
    shaka::eval::Lambda())->get_data());
    std::vector<std::shared_ptr<shaka::IDataNode<shaka::Data>>> args;
    auto result_vector = procedure.call(args);
    ASSERT_EQ(procedure.get_fixed_arity(), 0);
    ASSERT_EQ(false, procedure.is_variable_arity());
    ASSERT_EQ(shaka::get<shaka::Number>(*result_vector[0]->get_data()), shaka::Number(2));
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
