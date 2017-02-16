#include "gtest/gtest.h"

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/variant.hpp>

#include "DataNode.h"
#include "Environment.h"

using DataTree = shaka::DataNode<
    boost::variant<
        int,
        std::function<int(int,int)>
    >
>;

using Environment =
    shaka::Environment<std::string, std::shared_ptr<DataTree>>;


TEST(Evaluator_basic, initialization) {
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>([](int left, int right){
        return left + right;
    });

    Environment env(nullptr);
    root->push_child(1);
    root->push_child(2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
