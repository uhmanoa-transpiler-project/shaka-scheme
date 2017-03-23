#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Lambda.h"
#include "Procedure.h"

using Data = shaka::Data;

using IDataTree = shaka::IDataNode<Data>;
using DataTree = shaka::DataNode<Data>;

using Environment =
    shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Evaluator_lambda, initialization) {
    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LAMBDA);

    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);
    
    root->push_child(shaka::MetaTag::LIST);
    root->push_child(shaka::MetaTag::LIST);

    root->get_child(0)->push_child(shaka::Symbol("a"));
    root->get_child(0)->push_child(shaka::Symbol("b"));

    //  constructing evaluator 
    shaka::Evaluator evaluator(
        root, env
    );
    std::size_t arity= shaka::get<shaka::Procedure>(*evaluator.evaluate(
    shaka::eval::Lambda())->get_data()).get_fixed_arity();

std::size_t size= 2;
    ASSERT_EQ(size, arity
        );
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
