#include "gtest/gtest.h"
#include "DataNode.h"

#include <functional>
#include <algorithm>
#include <numeric>

using DataTree = shaka::DataNode<shaka::Data>;

/// @brief Basic default constructor test
TEST(DataNode, constructor_default) {
    DataTree root(shaka::MetaTag::NULL_LIST);

    ASSERT_TRUE(true);
}

TEST(DataNode, create_list) {
    // Create a root node with a list
    auto root = std::make_shared<DataTree>(shaka::MetaTag::LIST);

    // Push children to the root node.
    root->push_child(1);
    root->push_child(2);
    root->push_child(3);

    // Get the pointer to the data of the first child
    auto first_child_ptr = root->get_child(0);

    // Get an `int` from the data pointer inside the DataNode.
    auto first_child_data = shaka::get<int>( *first_child_ptr->get_data() );

    // Is 1 == first_child_data?
    ASSERT_EQ(1, first_child_data);

    // Get the parent of the first child
    auto first_childs_parent = first_child_ptr->get_parent();

    // Is the first child's parent root?
    ASSERT_EQ(first_childs_parent, root);
}

TEST(DataNode, create_and_verify_list) {
    // Create a LIST root node, and then 
    // push three ints that should add up to 10.
    //
    // Then, using ONLY the root node,
    // get the three children,
    // get the ints from them
    // add them together
    // and assert that their sum is equal to 10.
    auto root = std::make_shared<DataTree>(shaka::MetaTag::LIST);

    root->push_child(0);
    root->push_child(1);
    root->push_child(9);

    auto var1 = shaka::get<int>(*root->get_child(0)->get_data());
    auto var2 = shaka::get<int>(*root->get_child(1)->get_data());
    auto var3 = shaka::get<int>(*root->get_child(2)->get_data());

    ASSERT_EQ(
        10,
        var1+var2+var3
    );
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
