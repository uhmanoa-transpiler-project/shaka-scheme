#include "gtest/gtest.h"
#include "Integer.h"

TEST(Integer, add_integer_and_real) {
	Integer i(5);
	Real r(7.5);

	Real r2(i + r);

	ASSERT_EQ(r2.get_value(), static_cast<float>(12.5));
}

TEST(Integer, sub_integer_and_real) {
	Integer i(10);
	Real r(9.25);

	Real r2(i - r);

	ASSERT_EQ(r2.get_value(), static_cast<float>(0.75));
}

TEST(Integer, mul_integer_and_real) {
	Integer i(7);
	Real r(1.5);

	Real r2(i * r);

	ASSERT_EQ(r2.get_value(), static_cast<float>(10.5));
}

TEST(Integer, div_integer_and_real) {
	Integer i(20);
	Real r(2.0);

	Real r2(i / r);

	ASSERT_EQ(r2.get_value(), static_cast<float>(10));
}

int main(int argc, char* argv[]) {

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
