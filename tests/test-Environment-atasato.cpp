#include "gtest/gtest.h"
#include "DataNode.h"
#include "Environment.h"

using Environment = shaka::Environment<std::string, shaka::DataNode<boost::variant<int, std::function<int(int, int)>>>>;

TEST(Environment, nullptr_constructor) {
    // Create environment with nullptr parent.
    Environment env(nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
