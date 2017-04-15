#include <gtest/gtest.h>

#include "core/base/DataNode.h"

#include <sstream>

using namespace shaka;

TEST(DataNode, pairs) {
    {
        DataNode n0({Number(1)}, {Number(2)});
        ASSERT_TRUE(n0.is_pair());
        ASSERT_FALSE(n0.is_null());
        ASSERT_FALSE(n0.is_list());

        DataNode head = *n0.car();
        ASSERT_EQ(head, DataNode(Number(1)));
        ASSERT_FALSE(head.is_pair());
        ASSERT_FALSE(head.is_null());
        ASSERT_FALSE(head.is_list());

        DataNode tail = *n0.cdr();
        ASSERT_EQ(tail, DataNode(Number(2)));
        ASSERT_FALSE(tail.is_pair());
        ASSERT_FALSE(tail.is_null());
        ASSERT_FALSE(tail.is_list());
        std::cout << n0 << std::endl;
    }

    {
        DataNode n0({Number(1)}, {NodePtr{nullptr}});
        ASSERT_TRUE(n0.is_pair());
        ASSERT_FALSE(n0.is_null());
        ASSERT_TRUE(n0.is_list());

        DataNode head = *n0.car();
        ASSERT_EQ(head, DataNode(Number(1)));
        ASSERT_FALSE(head.is_pair());
        ASSERT_FALSE(head.is_null());
        ASSERT_FALSE(head.is_list());

        DataNode tail = *n0.cdr();
        ASSERT_EQ(tail, DataNode(NodePtr(nullptr)));
        ASSERT_FALSE(tail.is_pair());
        ASSERT_TRUE(tail.is_null());
        ASSERT_TRUE(tail.is_list());
        std::cout << n0 << std::endl;
    }

    {
        DataNode n0({Number(1)}, {NodePtr{nullptr}});
        ASSERT_TRUE(n0.is_pair());
        ASSERT_FALSE(n0.is_null());
        ASSERT_TRUE(n0.is_list());

        DataNode n1 = DataNode::cons({Number(0)}, n0);
        ASSERT_EQ(*n1.car(), DataNode(Number(0)));
        std::cout << n1 << std::endl;
    }

    {
        DataNode n0({Number(0)}, {NodePtr{nullptr}});
        for (int i = 1; i <= 10; ++i) {
            n0 = DataNode::cons({Number(i)}, n0);
        }

        for (int i = 0; i < 10; ++i) {
            auto temp = n0;
            for (int j = 0; j < i; ++j) {
                temp = *temp.cdr();
            }
            ASSERT_EQ(*temp.car(), DataNode(Number(10-i)));

        }
        std::cout << n0 << std::endl;
    }
}

TEST(DataNode, lists) {
    DataNode l0 =
        DataNode::list(Number(1), Number(2), Number(3), Number(4));
    std::cout << l0 << std::endl;

    DataNode l1 =
        DataNode::list(
            Symbol("define"),
            Symbol("x"),
            DataNode::list(
                Symbol("+"),
                Number(1),
                Number(2)
            )
        );
    std::cout << l1 << std::endl;
}

// Expectation:
// (quote (a b c))
TEST(DataNode, quote) {

    DataNode l0 = 
        DataNode::list(
            Symbol("quote"),
            DataNode::list(
                Symbol("a"),
                Symbol("b"),
                Symbol("c")
            )
        );
    std::cout << l0 << std::endl;
    ASSERT_TRUE(true);
}

// Expectation:
// (quote (a b c))
TEST(DataNode, quote_recursive_model) {

    DataNode l1 = 
        DataNode::list(
            Symbol("a"),
            Symbol("b"),
            Symbol("c")
        );

    DataNode l0 = 
        DataNode::list(
            Symbol("quote"),
            l1
        );
    std::cout << l0 << std::endl;
    ASSERT_TRUE(true);
}

// Expectation:
// (quote (a b c))
TEST(DataNode, quote_cons) {

    DataNode innerList(Symbol("a"));
    innerList = DataNode::list(innerList, Symbol("b"));
    innerList = DataNode::list(innerList, Symbol("c"));

    DataNode node(Symbol("quote"));
    node = DataNode::list(node, innerList);
    std::cout << node << std::endl;
    ASSERT_TRUE(true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
