#include "gtest/gtest.h"

#include "Environment.h"

TEST(Environment, test_environment_default_constructor) {
	shaka::Environment<int, int*> e(nullptr);

	ASSERT_EQ(e.get_parent(), nullptr);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
