#include "gtest/gtest.h"
#include "Rational.h"

TEST(Rational, add_rational_and_real) {
	Rational rat(1, 2);
	Real r(0.75);

	Real r2(rat + r);

	ASSERT_EQ(r2.get_value(), static_cast<float>(1.25));
}

TEST(Rational, sub_rational_and_real) {
	Rational rat(1, 2);
	Real r(0.75);
	
	Real r2(r - rat);

	ASSERT_EQ(r2.get_value(), static_cast<float>(0.25));
}

TEST(Rational, mul_rational_and_real) {
	Rational rat(1, 4);
	Real r(0.25);

	Real r2(rat * r);

	ASSERT_EQ(r2.get_value(), static_cast<float>(0.0625));
}

TEST(Rational, div_rational_and_real) {
	Rational rat(1, 2);
	Real r(0.25);

	Real r2(rat / r);

	ASSERT_EQ(r2.get_value(), static_cast<float>(2.0));
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
