#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Boolean.h"
#include "Eval_Boolean_impl.h"
#include "Boolean.h"

#include "Procedure.h"

using Data = shaka::Data;

using IDataTree = shaka::IDataNode<Data>;
using DataTree = shaka::DataNode<Data>;

using Environment =
    shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;


TEST(Evaluator_Boolean, boolean_true) {


    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::Boolean(true));

    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    //  constructing evaluator 
    shaka::Evaluator evaluator(
        root, env
    );

    ASSERT_EQ(shaka::Boolean(true), 
        shaka::get<shaka::Boolean>(*evaluator.evaluate(
    shaka::eval::Boolean())->get_data())
        );
}
TEST(Evaluator_Boolean, boolean_false) {


    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::Boolean(false));

    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    //  constructing evaluator 
    shaka::Evaluator evaluator(
        root, env
    );

    ASSERT_EQ(shaka::Boolean(false), 
        shaka::get<shaka::Boolean>(*evaluator.evaluate(
    shaka::eval::Boolean())->get_data())
        );
}

TEST(Evaluator_Boolean, boolean_not_false) {
    // anything other than false should evaluate to true
    
    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::Number(0));

    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    //  constructing evaluator 
    shaka::Evaluator evaluator(
        root, env
    );

    ASSERT_EQ(shaka::Boolean(true), 
        shaka::get<shaka::Boolean>(*evaluator.evaluate(
    shaka::eval::Boolean())->get_data())
        );

        // Made the root node.
    std::shared_ptr<DataTree> root2 = std::make_shared<DataTree>(shaka::Symbol("a"));

    //  constructing evaluator 
    shaka::Evaluator evaluator2(
        root2, env
    );

    ASSERT_EQ(shaka::Boolean(true), 
        shaka::get<shaka::Boolean>(*evaluator2.evaluate(
    shaka::eval::Boolean())->get_data())
        );    
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}