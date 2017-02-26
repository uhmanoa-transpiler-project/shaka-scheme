#include "gtest/gtest.h"
#include "Number.h"

TEST(Number, test_number_addition) {
	shaka::Number n1(10);
	shaka::Number n2(25);

	shaka::Number n3(n1 + n2);

	ASSERT_EQ(n3, shaka::Number(35));

}

TEST(Number, test_addition_rationals) {
	shaka::Number n1(1);
	shaka::Number n2(1, 2);
	shaka::Number n3(1, 4);

	shaka::Number n4(n1 + n2);
	shaka::Number n5(n2 + n3);

	ASSERT_EQ(n4, shaka::Number(3, 2));
	ASSERT_EQ(n5, shaka::Number(3, 4));
}

TEST(Number, test_number_subtraction) {
	shaka::Number n1(20.5);
	shaka::Number n2(10);

	shaka::Number n3(n1 - n2);

	ASSERT_EQ(n3, shaka::Number(10.5));
}

TEST(Number, test_subtraction_rationals) {
	shaka::Number n1(1);
	shaka::Number n2(1, 2);
	shaka::Number n3(0.5);

	shaka::Number n4(n1 - n2);
	shaka::Number n5((n1 + n3) - n2);

	ASSERT_EQ(n4, shaka::Number(1, 2));
	ASSERT_EQ(n5, shaka::Number(1));
	
}

TEST(Number, test_number_multiplication) {
	shaka::Number n1(2.0);
	shaka::Number n2(0.5);

	shaka::Number n3(n1 * n2);

	ASSERT_EQ(n3, shaka::Number(1));

}

TEST(Number, test_multiplication_rationals) {
	shaka::Number n1(1);
	shaka::Number n2(2);
	shaka::Number n3(1, 4);

	shaka::Number n4(n1 * n3);
	shaka::Number n5(n2 * n3);

	ASSERT_EQ(n4, shaka::Number(1, 4));
	ASSERT_EQ(n5, shaka::Number(1, 2));


}

TEST(Number, test_number_division) {
	shaka::Number n1(10);
	shaka::Number n2(2.0);

	shaka::Number n3(n1 / n2);

	ASSERT_EQ(n3, shaka::Number(5));
}

TEST(Number, test_division_rationals) {
	shaka::Number n1(1, 2);
	shaka::Number n2(2);
	shaka::Number n3(4.5);
	shaka::Number n4(1, 4);

	shaka::Number n5(n1 / n4);
	shaka::Number n6(n2 / n1);
	shaka::Number n7(n3 / n1);

	ASSERT_EQ(n5, shaka::Number(2));
	ASSERT_EQ(n6, shaka::Number(4));
	ASSERT_EQ(n7, shaka::Number(9));
}

TEST(Number, test_number_comparison) {
	shaka::Number n1(10);
	shaka::Number n2(10.0);
	shaka::Number n3(10.000);
	shaka::Number n4(10.5);

	ASSERT_EQ(n1 == n2, true);
	ASSERT_EQ(n1 == n3, true);
	ASSERT_EQ(n1 == n4, false);
	ASSERT_EQ(n1 < n4, true);
	ASSERT_EQ(n4 > n1, true);
	ASSERT_EQ(n1 <= n4, true);
	ASSERT_EQ(n4 >= n1, true);
}

TEST(Number, test_comparison_rationals) {
	shaka::Number n1(1);
	shaka::Number n2(0.5);
	shaka::Number n3(0.25);
	shaka::Number n4(1, 4);
	shaka::Number n5(1, 2);

	ASSERT_EQ(n2 == n5, true);
	ASSERT_EQ(n3 == n4, true);
	ASSERT_EQ(n1 > n5, true);
	ASSERT_EQ(n4 < n2, true);
	ASSERT_EQ(n5 >= n4, true);
	ASSERT_EQ(n3 <= n4, true);
	ASSERT_EQ(n4 != n5, true);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}
