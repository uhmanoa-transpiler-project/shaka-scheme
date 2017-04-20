#include "gtest/gtest.h"
#include "core/base/Complex.h"

TEST(Complex, add_two_complex_numbers) {
	shaka::Complex c1(5.0, 100);
	shaka::Complex c2(7, 40);

	shaka::Complex c3(c1 + c2);

	ASSERT_EQ(c3.get_real(), static_cast<double>(12.0));
	ASSERT_EQ(c3.get_imag(), static_cast<double>(140));
}

TEST(Complex, subtract_two_complex_numbers) {
	shaka::Complex c1(5.0, 20);
	shaka::Complex c2(7, 10);

	shaka::Complex c3(c1 - c2);

	ASSERT_EQ(c3.get_real(), static_cast<double>(-2));
	ASSERT_EQ(c3.get_imag(), static_cast<double>(10));
}

TEST(Complex, multiply_two_complex_numbers) {
	shaka::Complex c1(5.9, 22);
	shaka::Complex c2(30, -40);

	shaka::Complex c3(c1 * c2);

	ASSERT_EQ(c3.get_real(), static_cast<double>(1057));
	ASSERT_EQ(c3.get_imag(), static_cast<double>(424));
}

TEST(Complex, divide_two_complex_numbers) {
	shaka::Complex c1(6, 4);
	shaka::Complex c2(2, 2);

	shaka::Complex c3(c1 / c2);

	ASSERT_EQ(c3.get_real(), static_cast<double>(2.5));
	ASSERT_EQ(c3.get_imag(), static_cast<double>(-0.5));


}
int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


