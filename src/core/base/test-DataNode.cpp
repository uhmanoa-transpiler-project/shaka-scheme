#include <gtest/gtest.h>

#include "core/base/DataNode.h"

#include <sstream>

using namespace shaka;

TEST(DataNode, single_item_constructor) {
    DataNode l0(NodePtr(nullptr));
    ASSERT_TRUE(l0.is_null());
    ASSERT_FALSE(l0.is_pair());

    DataNode l1(shaka::Number(1));
    ASSERT_FALSE(l1.is_null());
    ASSERT_FALSE(l1.is_pair());

    DataNode l2 = DataNode::cons(l1, l0);
    ASSERT_FALSE(l2.is_null());
    ASSERT_TRUE(l2.is_pair());
}

TEST(DataNode, single_item_print) {
    std::ostringstream oss;

    DataNode l0(NodePtr(nullptr));
    DataNode l1(shaka::Number(1));
    DataNode l2(shaka::Symbol("asdf"));
    DataNode l3(shaka::String("Hello"));
    DataNode l4(shaka::Boolean(true));
    DataNode l5(std::make_shared<Environment>(nullptr));

    oss << l0;
    ASSERT_EQ(oss.str(), std::string("()"));
    oss.str(std::string());
    
    oss << l1;
    ASSERT_EQ(oss.str(), std::string("1"));
    oss.str(std::string());

    oss << l2;
    ASSERT_EQ(oss.str(), std::string("asdf"));
    oss.str(std::string());

    oss << l3;
    ASSERT_EQ(oss.str(), std::string("\"Hello\""));
    oss.str(std::string());

    oss << l4;
    ASSERT_EQ(oss.str(), std::string("#t"));
    oss.str(std::string());

    oss << l5;
    ASSERT_EQ(oss.str(), std::string("#<environment>"));
    oss.str(std::string());
}

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

/// @brief Basic default constructor test
TEST(DataNode, constructors) {
    // '()
    shaka::DataNode l0(NodePtr(nullptr));
    ASSERT_TRUE(l0.is_null());
    ASSERT_TRUE(l0.is_list());
    ASSERT_FALSE(l0.is_pair());
    ASSERT_EQ(0, l0.length());
    std::cout << l0 << std::endl;

    // 1
    shaka::DataNode l1(shaka::Number(1));
    ASSERT_FALSE(l1.is_null());
    ASSERT_FALSE(l1.is_list());
    ASSERT_FALSE(l1.is_pair());
    ASSERT_EQ(shaka::DataNode(shaka::Number(1)), l1);
    std::cout << l1 << std::endl;

    // (1 . 2)
    shaka::DataNode l2({shaka::Number(1)}, {shaka::Number(2)});
    ASSERT_FALSE(l2.is_null());
    ASSERT_FALSE(l2.is_list());
    ASSERT_TRUE(l2.is_pair());
    ASSERT_EQ(shaka::DataNode({shaka::Number(1)}, {shaka::Number(2)}), l2);
    std::cout << l2 << std::endl;

    // (1 . '()) or (1)
    shaka::DataNode l3({shaka::Number(1)}, {NodePtr(nullptr)});
    ASSERT_FALSE(l3.is_null());
    ASSERT_TRUE(l3.is_list());
    ASSERT_TRUE(l3.is_pair());
    ASSERT_EQ(1, l3.length());
    std::cout << l3 << std::endl;
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

    DataNode l2 = DataNode::list();
    std::cout << l2 << std::endl;
}

TEST(DataNode, append) {
    DataNode l0 = DataNode::list(Symbol("x"));
    l0.append(DataNode::list(Symbol("y")));
    std::cout << l0 << std::endl;

    DataNode l1 = DataNode::list(Symbol("a"));
    l1.append(
        DataNode::list(
            Symbol("b"),
            Symbol("c"),
            Symbol("d")));
    std::cout << l1 << std::endl;

    DataNode l2 = DataNode::list(
        Symbol("a"),
        DataNode::list(
            Symbol("b")));
    l2.append(
        DataNode::list(
            DataNode::list(
                Symbol("c"))));
    std::cout << l2 << std::endl;

    DataNode l3 = DataNode::list(
        Symbol("a"),
        Symbol("b"));
    l3.append(
        DataNode::cons(
            DataNode(Symbol("c")),
            DataNode(Symbol("d"))));
    std::cout << l3 << std::endl;

    DataNode l4 = DataNode::list();
    l4.append(DataNode(Symbol("a")));
    std::cout << l4 << std::endl;
}

/*
TEST(DataNode, types) {
    shaka::DataNode l0(shaka::Number(1));
    shaka::DataNode l1(shaka::Symbol("asdf"));
    shaka::DataNode l2(shaka::String("Hello world!"));
    shaka::DataNode l3(shaka::Boolean(true));
    shaka::DataNode l4(shaka::Environment(nullptr));
    shaka::DataNode l5(
        std::make_shared<shaka::DataNode>(shaka::Number(123), shaka::Number(100)),
        std::make_shared<shaka::DataNode>(shaka::Number(456)));

    std::cout << l0 << std::endl;
    std::cout << l1 << std::endl;
    std::cout << l2 << std::endl;
    std::cout << l3 << std::endl;
    std::cout << l4 << std::endl;
    std::cout << l5 << std::endl;
}

TEST(DataNode, lists) {
    // 1
    shaka::DataNode l0(std::make_shared<shaka::DataNode>(shaka::Number(1)));
    std::cout << l0 << std::endl;

    // (1 . (2 . (3 . (4 . '())))) or (1 2 3 4)

    shaka::DataNode l1(nullptr, nullptr);
    std::cout << l1 << std::endl;
    l1 = shaka::DataNode::cons(shaka::Number(4), l1);
    std::cout << l1 << std::endl;
    l1 = shaka::DataNode::cons(shaka::Number(3), l1);
    std::cout << l1 << std::endl;
    l1 = shaka::DataNode::cons(shaka::Number(2), l1);
    std::cout << l1 << std::endl;
    l1 = shaka::DataNode::cons(shaka::Number(1), l1);
    std::cout << l1 << std::endl;
}


//TEST(DataNode, mock_eval) {
//    shaka::DataNode expr(shaka::Symbol("define"));
//
//    expr = expr.cons(shaka::Symbol("a"));
//    expr = expr.cons(shaka::Number(1));
//}

*/
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
