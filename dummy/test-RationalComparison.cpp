#include "gtest/gtest.h"
#include "Rational.h"

TEST(Rational, rational_equality) {
	shaka::Rational r1(1,2);
	shaka::Rational r2(2,4);

	ASSERT_EQ(r1 == r2, true);
}

TEST(Rational, rational_gt) {
	shaka::Rational r1(1, 2);
	shaka::Rational r2(1, 4);

	ASSERT_EQ(r1 > r2, true);
}

TEST(Rational, rational_lt) {
	shaka::Rational r1(1, 8);
	shaka::Rational r2(1, 2);

	ASSERT_EQ(r1 < r2, true);
}

TEST(Rational, rational_geq) {
	shaka::Rational r1(3, 8);
	shaka::Rational r2(6, 16);
	shaka::Rational r3(1, 8);

	ASSERT_EQ(r1 >= r2, true);
	ASSERT_EQ(r1 >= r3, true);
}

TEST(Rational, rational_leq) {
	shaka::Rational r1(1, 6);
	shaka::Rational r2(2, 6);
	shaka::Rational r3(2, 12);

	ASSERT_EQ(r1 <= r2, true);
	ASSERT_EQ(r1 <= r3, true);
}

TEST(Rational, rational_neq) {
	shaka::Rational r1(1, 6);
	shaka::Rational r2(3, 12);

	ASSERT_EQ(r1 != r2, true);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
