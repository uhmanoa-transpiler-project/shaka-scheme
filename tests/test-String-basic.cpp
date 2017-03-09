#include "String.h"
#include "gtest/gtest.h"

TEST(Rational, rational_neq) {
	Rational r1(1, 6);
	Rational r2(3, 12);

	ASSERT_EQ(r1 != r2, true);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
