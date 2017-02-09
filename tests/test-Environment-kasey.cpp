#include "gtest/gtest.h"
#include "Environment.h"

using namespace shaka;
TEST(Environment, define_and_find_key) {
    Environment e;
    e.define("first", 2);

    ASSERT_EQ(2, *e.find("first"));
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
