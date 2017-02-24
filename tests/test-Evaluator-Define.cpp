#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Define.h"

using Data = shaka::Data;

using IDataTree = shaka::IDataNode<Data>;
using DataTree = shaka::DataNode<Data>;

using Environment =
    shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;


TEST(Evaluator_define, initialization) {
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::DEFINE);

    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);
    root->push_child(shaka::Symbol("a"));
    root->push_child(1);

    // /* constructing evaluator */
    shaka::Evaluator<Data, shaka::Symbol, std::shared_ptr<IDataTree>> evaluator(
        env,
        root
    );

    evaluator.evaluate(shaka::eval::Define<
        Data,
        shaka::Symbol,
        std::shared_ptr<IDataTree>
    >());
   ASSERT_EQ(1, shaka::get<int>(*env->get_value(shaka::Symbol("a"))->get_data()));
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
