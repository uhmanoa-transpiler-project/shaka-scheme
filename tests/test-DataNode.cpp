#include "gtest/gtest.h"
#include "DataNode.h"

TEST(DataNode, assign_and_get_int) {
    shaka::DataNode node;
    node.data = 1;

    int i = shaka::get<int>(node.data);

    ASSERT_EQ(i, static_cast<int>(1));
}


/// Tests whether the DataNode 
TEST(DataNode, construct_with_bool) {
    shaka::DataNode node(true);

    bool b = shaka::get<bool>(node.data);

    ASSERT_EQ(b, static_cast<bool>(true));
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
