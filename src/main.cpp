#include <gtest/gtest.h>

#include "Data.h"
#include "Procedure.h"


TEST(Data, construct) {
    std::cout << "hello world" << std::endl;

    shaka::Data d = shaka::Symbol("Hello world!");
    d = shaka::Number(1);

}

#include "DataNode.h"
#include <memory>

using DataNode = shaka::DataNode<shaka::Data>;

TEST(DataNode, construct) {
    auto root = std::make_shared<DataNode>(shaka::MetaTag::LIST);

    auto child0 = root->push_child(shaka::Number(1));

    auto num = shaka::get<shaka::Number>(*root->get_child(0)->get_data());

    ASSERT_EQ(num, shaka::Number(1));

    root->push_child(1);
    root->push_child(1);
    root->push_child(1);
    root->push_child(1);

    ASSERT_EQ(root->get_num_children(), 5);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
