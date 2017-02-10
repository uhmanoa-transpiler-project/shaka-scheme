#include "gtest/gtest.h"
#include "Number.h"

TEST(Number, test_number_arithmetic) {
	shaka::Number n1(10);
	shaka::Number n2(25);

	shaka::Number n3(n1 + n2);
	shaka::Number n4(n2 - n1);
	shaka::Number n5(n1 * n2);
	shaka::Number n6(n1 / n2);

	ASSERT_EQ(n3.get_Value(), static_cast<double>(35));
	ASSERT_EQ(n4.get_Value(), static_cast<double>(15));
	ASSERT_EQ(n5.get_Value(), static_cast<double>(250));
	ASSERT_EQ(n6.get_Value(), static_cast<double>(0.4));

}

TEST(Number, test_number_comparison) {
	shaka::Number n1(10);
	shaka::Number n2(10);
	shaka::Number n3(5);

	ASSERT_EQ(n1 == n2, true);
	ASSERT_EQ(n1 != n2, false);
	ASSERT_EQ(n1 > n3, true);
	ASSERT_EQ(n1 >= n2, true);
	ASSERT_EQ(n3 < n1, true);

}

TEST(Number, test_exact_inexact_representation) {
	shaka::Number n1(10.5);

	shaka::Number n2(20);

	ASSERT_EQ(shaka::exact_p(n1), false);
	ASSERT_EQ(shaka::exact_p(n2), true);
	ASSERT_EQ(shaka::inexact_p(n1), true);
	ASSERT_EQ(shaka::inexact_p(n2), false);

}


int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}
