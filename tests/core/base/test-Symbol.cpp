#include "gtest/gtest.h"
#include "core/base/Symbol.h" 

TEST(Symbol, a_symbol){
	shaka::Symbol n1("symbol");
	shaka::Symbol n2("burrito");

	ASSERT_EQ(n1 == n2, false);
}

TEST(Symbol, check_equal_symbol){
	shaka::Symbol n1("bird");
	shaka::Symbol n2("bird");

	ASSERT_EQ(n1 == n2, true);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
