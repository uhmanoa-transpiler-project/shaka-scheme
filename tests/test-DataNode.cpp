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
/// @brief Tests forwarding of arguments to internal data.
TEST(DataNode, init_int) {

    /// @todo Use the real Number class in the DataNode.
    DataTree root(1);

    // Test getting the same value we initialized the root node tree with.
    auto result = shaka::get<int>(*root.get_data());

    ASSERT_EQ(result, 1);
}

/// @brief Pushes a DataNode to the root's children and compares
///        by value and by pointer value.
TEST(DataNode, push_and_get_child) {

    // Initialize the root with first part of Hello world
    //
    // @note YOU NEED TO USE A SHARED_PTR TO HOLD THE ROOT.
    //       OTHERWISE, ADDING CHILDREN WILL NOT WORK!
    auto root = std::make_shared<DataTree>( 
        std::string("Hello ")
    );

    // Create a std::shared_ptr to a node.
    auto node = std::make_shared<DataTree>(
        std::string("world!")
    );

    // Add that node to the tree.
    root->push_child(*node->get_data());

    // Get the child node.
    auto result_node = shaka::get<std::string>(*node->get_data());
    auto result_child = shaka::get<std::string>(
        *root->get_last_child()->get_data()
    );

    // Compare the two child nodes by value.
    ASSERT_EQ(result_node, result_child);

    // Make sure that the outside node and the internal tree node
    // do not have the same pointer value.
    ASSERT_NE(node, root->get_child(0));
}

/// @brief Pushes various nodes to the root and checks for
///        the correct amount of children returned.
TEST(DataNode, get_num_children) {

    auto root = std::make_shared<DataTree>(0);

    ASSERT_EQ(root->get_num_children(), std::size_t(0));

    root->push_child(1);
    root->push_child(2);

    ASSERT_EQ(root->get_num_children(), std::size_t(2));

    root->push_child(2);
    root->push_child(2);
    root->push_child(2);
    root->push_child(2);
    root->push_child(2);
    root->push_child(2);

    ASSERT_EQ(root->get_num_children(), std::size_t(8));

// Note: this worked when I last tested it,
// but the test should only rely on push_child() and get_num_children()
//     root.remove_child(7);
//     root.remove_child(4);
//     root.remove_child(2);
//     root.remove_child(0);
//     root.remove_child(1);
//
//     ASSERT_EQ(root.get_num_children(), std::size_t(3));
}

/// @brief Pushes, and then removes a child by index.
TEST(DataNode, remove_child) {
    // Initialize the root node with a boolean value.
    auto root = std::make_shared<DataTree>(true);

    // The value to test for.
    std::string test_value("shaka-scheme");

    // Push a child with a std::string value.
    root->push_child(test_value);

    // See if the child value matches.
    ASSERT_EQ(
        shaka::get<std::string>(*root->get_child(0)->get_data()),
        test_value
    );

    // Remove the only child.
    root->remove_child(0);

    // The current convention is to return a nullptr for invalid values.
    ASSERT_EQ(
        root->get_child(0),
        nullptr
    );
}


/// @brief Applies a function that simply prints out the contents of the tree
///        using post-order traversal.
TEST(DataNode, traverse_tree_pre_order_print) {
    // Create a full tree of depth 2, ordered
    // pre-order.
    std::shared_ptr<DataTree> root =
        std::make_shared<DataTree>(1);

    auto left           = root->push_child(2);
    auto left_left      = left->push_child(3);
    auto left_right     = left->push_child(4);
    auto right          = root->push_child(5);
    auto right_left     = right->push_child(6);
    auto right_right    = right->push_child(7);

    using NodeTree = shaka::IDataNode<shaka::Data>;

    // Must use std::function and capture by reference
    // in order to do a recursive lambda.
    std::function<void(std::shared_ptr<NodeTree>)> pre_order_print;
    // The pre-order printing function.
    std::vector<int> v;
    pre_order_print = [&pre_order_print, &v](std::shared_ptr<NodeTree> tree) -> void {
        if (tree) {
            if (int* ptr = shaka::get<int>(tree->get_data().get())) {
                v.push_back(*ptr);
                // std::cout << *ptr << std::endl;
                pre_order_print(tree->get_child(0));
                pre_order_print(tree->get_child(1));
            } else {
                throw std::runtime_error("ERROR: Node data is not an `int`!");
            }
        }
    };

    // Apply the function to the tree.
    pre_order_print(root);


    std::vector<int> correct_traversal_order = {1, 2, 3, 4, 5, 6, 7};
    // Check whether the traversal order was correct, according to the
    // numbers we kept track of by pushing to the vector in the printing function.
    ASSERT_TRUE(
        std::equal(
            v.begin(),
            v.begin() + v.size(),
            correct_traversal_order.begin()
        )
    );

}


/// @brief Applies a function that return the sum of the tree,
///        using post-order traversal.
TEST(DataNode, traverse_tree_post_order_sum) {
    // Create a full tree of depth 2, ordered
    // pre-order.
    std::shared_ptr<DataTree> root =
        std::make_shared<DataTree>(7);

    auto left           = root->push_child(3);
    auto left_left      = left->push_child(1);
    auto left_right     = left->push_child(2);
    auto right          = root->push_child(6);
    auto right_left     = right->push_child(4);
    auto right_right    = right->push_child(5);

    using NodeTree = shaka::IDataNode<shaka::Data>;

    // Must use std::function and capture by reference
    // in order to do a recursive lambda.
    std::function<int(std::shared_ptr<NodeTree>)> post_order_sum;

    // The vector to keep track of which nodes were traversed first.
    std::vector<int> v;
    post_order_sum = [&post_order_sum, &v](std::shared_ptr<NodeTree> tree) -> int {
        if (tree) {
            if (int* ptr = shaka::get<int>(tree->get_data().get())) {
                int sum_left = post_order_sum(tree->get_child(0));
                int sum_right = post_order_sum(tree->get_child(1));
                v.push_back(*ptr);
                // std::cout << *ptr << std::endl;
                return sum_left + sum_right + *ptr;
            } else {
                throw std::runtime_error("ERROR: Node data is not an `int`!");
                return -1;
            }
        } else {
            return 0;
        }
    };

    // Apply the function to the tree.
    int sum = post_order_sum(root);


    std::vector<int> correct_traversal_order = {1, 2, 3, 4, 5, 6, 7};
    // Check whether the traversal order was correct, according to the
    // numbers we kept track of by pushing to the vector in the printing function.
    ASSERT_TRUE(
        std::equal(
            v.begin(),
            v.begin() + v.size(),
            correct_traversal_order.begin()
        )
    );

    // Make sure that the calculated sum matches the ideal traversal order log
    ASSERT_EQ(
        std::accumulate(
            correct_traversal_order.begin(),
            correct_traversal_order.end(),
            0
        ),
        sum
    );

    // Make sure that the calculated sum matches the recordeed traversal log
    ASSERT_EQ(
        std::accumulate(
            v.begin(),
            v.end(),
            0
        ),
        sum
    );
}

/// @todo In-order traversal of a tree.

/// @brief Pushes, and then removes a child by index.
TEST(DataNode, get_parent) {
    // Initialize the root node with a boolean value.
    auto root = std::make_shared<DataTree>(true);

    // Push a child node, initialized with a value.
    auto child = root->push_child(false);

    // Push a grandchild node to the child
    auto grandchild = child->push_child(true);

    // See if the child's parent is the same as the root
    ASSERT_EQ(
        root,
        root->get_child(0)->get_parent()
    );

    // See if the grandchild's parent is the same as the root's child
    ASSERT_EQ(
        grandchild->get_parent(),
        child
    );

    // Remove the only child of the root, but it should remain alive.
    root->remove_child(0);

    /// @note Children that are removed from a parent's list are
    ///       are not necessarily deleted from the program.
    ///       Nodes that need a reference to the grandparent
    ///       will still keep their deleted parent alive.
    // Check that we can still reach the parent though nodes that
    // reference it.
    ASSERT_EQ(
        grandchild->get_parent()->get_parent(),
        root
    );
}
/// @todo Test node insertion with insert_node()

/// @todo Test set_node()
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
