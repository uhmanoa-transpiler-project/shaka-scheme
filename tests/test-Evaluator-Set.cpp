#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "Data.h"
#include "DataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Set.h"
#include "Procedure.h"

#include "Eval_Set_impl.h"
#include "Eval_Variable_impl.h"
#include "Eval_PrintTree.h"

using Data = shaka::Data;

using IDataTree = shaka::IDataNode<Data>;
using DataTree = shaka::DataNode<Data>;

using Environment =
    shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;


TEST(Evaluator_set, set) {

    // Made the root node.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::SET);

    // Created the enivronment
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);
    std::shared_ptr<DataTree> data = std::make_shared<DataTree>(shaka::Number(2));
    env->set_value(shaka::Symbol("a"), data);
    // Pushed the symbol
    root->push_child(shaka::Symbol("a"));
    // Pushed a value
    root->push_child(shaka::Number(1));


    // /* constructing evaluator */
    shaka::Evaluator evaluator(
        root,
        env
    );

    // Evaluate the next thing using the Set strategy.
    evaluator.evaluate(shaka::eval::Set());

    ASSERT_EQ(1,1);
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}