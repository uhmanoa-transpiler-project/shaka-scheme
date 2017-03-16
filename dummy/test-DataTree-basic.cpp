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


TEST(DataTree, initialization) {
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>([](int left, int right){
        return left + right;
    });

    root->push_child(1);
    root->push_child(2);
}

TEST(DataTree, get_function) {
    // Initialize the root node with a function.
    std::shared_ptr<DataTree> root = std::make_shared<DataTree>([](int left, int right){
        return left + right;
    });

    // Just intiialize an empty environment.
    root->push_child(1);
    root->push_child(2);

    // Get the data.
    auto fn     = shaka::get<std::function<int(int,int)>>(*root->get_data());
    auto val1   = shaka::get<int>(*root->get_child(0)->get_data());
    auto val2   = shaka::get<int>(*root->get_child(1)->get_data());

    // Call the function, and compare its result.
    ASSERT_EQ(
        3,
        fn(val1, val2)
    );

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
