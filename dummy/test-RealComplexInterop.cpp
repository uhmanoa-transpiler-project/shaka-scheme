#include "gtest/gtest.h"
#include "Real.h"

using namespace shaka;

TEST(Real, add_real_to_complex) {
	Complex c1(5.0, 4);
	Real r1(20);

	Complex c3(r1 + c1);

	ASSERT_EQ(c3.get_real(), static_cast<float>(25.0));
	ASSERT_EQ(c3.get_imag(), static_cast<float>(4));
}

TEST(Real, sub_real_from_complex) {
	Complex c1(10, -6);
	Real r1(5);

	Complex c3(c1 - r1);

	ASSERT_EQ(c3.get_real(), static_cast<float>(5));
	ASSERT_EQ(c3.get_imag(), static_cast<float>(-6));
}

TEST(Real, mul_real_and_complex) {
	Complex c1(23, 10);
	Real r1(7);

	Complex c3(c1 * r1);

	ASSERT_EQ(c3.get_real(), static_cast<float>(161));
	ASSERT_EQ(c3.get_imag(), static_cast<float>(70));

}

TEST(Real, div_real_and_complex) {
	Complex c1(20, 5);
	Real r1(5);

	Complex c3(c1 / r1);

	ASSERT_EQ(c3.get_real(), static_cast<float>(4));
	ASSERT_EQ(c3.get_imag(), static_cast<float>(1));
}
int main(int argc, char* argv[]) {

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
