#include "gtest/gtest.h"
#include "Rational.h"

TEST(Rational, add_two_rational_numbers) {
	shaka::Rational r1(1, 3);
	shaka::Rational r2(1, 4);

	shaka::Rational r3(r1 + r2);

	ASSERT_EQ(r3.get_numerator(), static_cast<float>(7));
	ASSERT_EQ(r3.get_denominator(), static_cast<float>(12));
}

TEST(Rational, sub_two_rational_numbers) {
	shaka::Rational r1(1, 2);
	shaka::Rational r2(1, 4);

	shaka::Rational r3(r1 - r2);

	ASSERT_EQ(r3.get_numerator(), static_cast<float>(2));
	ASSERT_EQ(r3.get_denominator(), static_cast<float>(8));
}

TEST(Rational, mul_two_rational_numbers) {
	shaka::Rational r1(1, 3);
	shaka::Rational r2(1, 3);

	shaka::Rational r3(r1 * r2);

	ASSERT_EQ(r3.get_numerator(), static_cast<float>(1));
	ASSERT_EQ(r3.get_denominator(), static_cast<float>(9));

}

TEST(Rational, div_two_rational_numbers) {
	shaka::Rational r1(1, 5);
	shaka::Rational r2(3, 4);

	shaka::Rational r3(r1 / r2);

	ASSERT_EQ(r3.get_numerator(), static_cast<float>(4));
	ASSERT_EQ(r3.get_denominator(), static_cast<float>(15));

}
int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}
