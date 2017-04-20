#include <gtest/gtest.h>

#include "core/base/Core.h"
#include "core/eval/Proccall_impl.h"
#include "core/eval/Define_impl.h"
#include <sstream>

using namespace shaka;

TEST(Proccall, initialization) {
    using namespace shaka;
    auto lambda_list = std::make_shared<DataNode>(DataNode::list(
        Symbol("lambda"),
        DataNode::list(Symbol("x")),
        Symbol("x")
    ));

    auto define_expr = std::make_shared<DataNode>(DataNode::list(
        Symbol("define"),
        Symbol("asdf")
    ));
    define_expr->append(*lambda_list);

    auto list = std::make_shared<DataNode>(DataNode::list(
        Symbol("define"),
        Symbol("asdf"),
        Number(1)
    ));

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
