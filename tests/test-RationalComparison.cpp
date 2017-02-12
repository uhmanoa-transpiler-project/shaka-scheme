#include "gtest/gtest.h"
#include "Rational.h"

TEST(Rational, rational_equality) {
	Rational r1(1,2);
	Rational r2(2,4);

	ASSERT_EQ(r1 == r2, true);
}

TEST(Rational, rational_gt) {
	Rational r1(1, 2);
	Rational r2(1, 4);

	ASSERT_EQ(r1 > r2, true);
}

TEST(Rational, rational_lt) {
	Rational r1(1, 8);
	Rational r2(1, 2);

	ASSERT_EQ(r1 < r2, true);
}

TEST(Rational, rational_geq) {
	Rational r1(3, 8);
	Rational r2(6, 16);
	Rational r3(1, 8);

	ASSERT_EQ(r1 >= r2, true);
	ASSERT_EQ(r1 >= r3, true);
}

TEST(Rational, rational_leq) {
	Rational r1(1, 6);
	Rational r2(2, 6);
	Rational r3(2, 12);

	ASSERT_EQ(r1 <= r2, true);
	ASSERT_EQ(r1 <= r3, true);
}

TEST(Rational, rational_neq) {
	Rational r1(1, 6);
	Rational r2(3, 12);

	ASSERT_EQ(r1 != r2, true);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
