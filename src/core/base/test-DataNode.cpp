#include <gtest/gtest.h>
#include "core/base/DataNode.h"

/// @brief Basic default constructor test
TEST(DataNode, constructors) {
    // '()
    shaka::DataNode l0(nullptr, nullptr);
    ASSERT_TRUE(l0.is_null());
    ASSERT_FALSE(l0.is_list());
    ASSERT_FALSE(l0.is_pair());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
