#include "gtest/gtest.h"
#include "DataNode.h"
#include "Environment.h"
#include <functional>
#include <algorithm>
#include <numeric>



using DataTree = shaka::DataNode<shaka::Data>;

TEST(Environment, default_constructorEnvironmentTest){

	using namespace shaka;

	ASSERT_EQ(1,1);
}

/// @todo Test node insertion with insert_node()

/// @todo Test set_node()
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
