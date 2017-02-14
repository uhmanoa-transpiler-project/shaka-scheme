#include "gtest/gtest.h"
#include "DataNode.h"

#include <functional>
#include <algorithm>
#include <numeric>

using DataTree = shaka::DataNode<shaka::Data>;

TEST(Evaluator_basic, initialization) {
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>("+");
    root->push_child(1);
    root->push_child(2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
