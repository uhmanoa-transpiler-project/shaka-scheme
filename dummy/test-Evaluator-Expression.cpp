
#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Expression.h"
#include "Procedure.h"

using Data = shaka::Data;
using IDataTree = shaka::IDataNode<Data>;
using DataTree = shaka::DataNode<Data>;

using Environment =
    shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Evaluator_Expression, define) {
    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::DEFINE);

    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);
    // Pushed the symbol
    root->push_child(shaka::Symbol("a"));
    // Pushed a value
    root->push_child(1);

    // /* constructing evaluator */
    shaka::Evaluator evaluator(
        root,
        env
    );

    // Evaluate the next thing using the Define strategy.
    evaluator.evaluate(shaka::eval::Expression());

    ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*env->get_value(shaka::Symbol("a"))->get_data()));
 
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
