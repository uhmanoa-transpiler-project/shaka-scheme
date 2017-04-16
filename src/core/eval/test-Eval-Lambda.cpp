#include <gtest/gtest.h>

#include "core/base/DataNode.h"
#include "core/eval/Lambda_impl.h"
#include "core/base/Procedure_impl.h"
#include "core/eval/ProcedureBody_impl.h"
#include <sstream>

using namespace shaka;

TEST(Lambda, single_item_constructor) {
ASSERT_TRUE(true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}