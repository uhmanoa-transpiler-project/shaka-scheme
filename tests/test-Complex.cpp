#include "gtest/gtest.h"
#include "Complex.h"

TEST(Complex, add_two_complex_numbers) {
	Complex c1(5.0, 100);
	Complex c2(7, 40);

	Complex c3(c1 + c2);

	ASSERT_EQ(c3.get_real(), static_cast<double>(12.0));
	ASSERT_EQ(c3.get_imag(), static_cast<double>(140));
}

TEST(Complex, subtract_two_complex_numbers) {
	Complex c1(5.0, 20);
	Complex c2(7, 10);

	Complex c3(c1 - c2);

	ASSERT_EQ(c3.get_real(), static_cast<double>(-2));
	ASSERT_EQ(c3.get_imag(), static_cast<double>(10));
}

TEST(Complex, multiply_two_complex_numbers) {
	Complex c1(5.9, 22);
	Complex c2(30, -40);

	Complex c3(c1 * c2);

	ASSERT_EQ(c3.get_real(), static_cast<double>(1057));
	ASSERT_EQ(c3.get_imag(), static_cast<double>(424));
}

TEST(Complex, divide_two_complex_numbers) {
	Complex c1(6, 4);
	Complex c2(2, 2);

	Complex c3(c1 / c2);

	ASSERT_EQ(c3.get_real(), static_cast<double>(2.5));
	ASSERT_EQ(c3.get_imag(), static_cast<double>(-0.5));


}
int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


