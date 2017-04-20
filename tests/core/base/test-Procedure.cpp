#include <gtest/gtest.h>

#include "core/base/Core.h"
#include "core/base/Procedure.h"

#include <sstream>

using namespace shaka;

TEST(Procedure,  single_item_constructor) {
    EnvPtr env = std::make_shared<Environment>(nullptr);
    ListPtr node = std::make_shared<DataNode>(DataNode::list(
        DataNode(Symbol("x")),
        DataNode(Symbol("x"))
        ));
    Procedure procedure(env, node, 0, true);
    ASSERT_EQ(procedure.get_fixed_arity(), 0);
    ASSERT_TRUE(procedure.is_variable_arity());

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
