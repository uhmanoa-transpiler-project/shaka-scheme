#include "gtest/gtest.h"
#include "Environment.h"



TEST(Environment, nullptr_constructor) {
    // Create environment with nullptr parent.
    shaka::Environment env(nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
