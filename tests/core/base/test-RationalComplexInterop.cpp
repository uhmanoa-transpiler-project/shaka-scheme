#include "gtest/gtest.h"
#include "core/base/Rational.h"

using namespace shaka;

TEST(Rational, add_rational_and_complex) {
	Rational r(1, 2);
	Complex c(5, 10);

	Complex c2(r + c);

	ASSERT_EQ(c2.get_real(), static_cast<double>(5.5));
	ASSERT_EQ(c2.get_imag(), static_cast<double>(10));
}

TEST(Rational, sub_rational_and_complex) {
	Rational r(1, 4);
	Complex c(5, 20);

	Complex c2(c - r);

	ASSERT_EQ(c2.get_real(), static_cast<double>(4.75));
	ASSERT_EQ(c2.get_imag(), static_cast<double>(20));
}

TEST(Rational, mul_rational_and_complex) {
	Rational r(3, 4);
	Complex c(10, -7);

	Complex c2(r * c);

	ASSERT_EQ(c2.get_real(), static_cast<double>(7.5));
	ASSERT_EQ(c2.get_imag(), static_cast<double>(-5.25));
}

TEST(Rational, div_rational_and_complex) {
	Rational r(1, 2);
	Complex c(2, 4);

	Complex c2(r / c);

	ASSERT_EQ(c2.get_real(), static_cast<double>(0.05));
	ASSERT_EQ(c2.get_imag(), static_cast<double>(-0.1));
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
