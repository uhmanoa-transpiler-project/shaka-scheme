#include <gtest/gtest.h>
#include "core/base/Core.h"
#include "core/macro/Pattern.h"

using namespace shaka;
using namespace shaka::macro;

TEST(Macro_Pattern, initialization) {
    
    ASSERT_NO_THROW({
        Pattern p(DataNode::list(
            Symbol("foo"),
            Symbol("bar")));
    });

    ASSERT_THROW({
        Pattern p1(DataNode(Symbol("a")));
    }, std::runtime_error);
}

TEST(Macro_Pattern, match_datum) {
    Pattern p(DataNode::list(
        Symbol("foo"),
        Symbol("bar")));

    ASSERT_THROW({
        Pattern::match_datum(
            DataNode(Symbol("a")),
            DataNode(Symbol("b")));
    }, std::runtime_error);

    ASSERT_FALSE(
        Pattern::match_datum(
            DataNode(Number(1, 2)),
            DataNode(Symbol("b"))));

    ASSERT_TRUE(
        Pattern::match_datum(
            DataNode(Number(1, 2)),
            DataNode(Number(1, 2))));
}

TEST(Macro_Pattern, match_datum_patterns) {
    Pattern p(DataNode::list(
        Symbol("foo"),
        Number(1)));

    DataNode l0 = DataNode::list(
        Symbol("wtf"),
        Number(1));

    DataNode l1 = DataNode::list(
        Symbol("wtf"),
        Number(2));

    DataNode l2 = DataNode::list(
        Symbol("wtf"),
        Number(1),
        Number(2));

    DataNode l3 = DataNode::list(
        Symbol("wtf"),
        String("Hello"),
        Number(2));

    ASSERT_TRUE(p.match(l0));
    ASSERT_FALSE(p.match(l1));
    ASSERT_FALSE(p.match(l2));
    ASSERT_FALSE(p.match(l3));
}

TEST(Macro_Pattern, match_ellipsis) {

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
