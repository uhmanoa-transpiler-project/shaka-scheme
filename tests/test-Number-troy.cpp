#include "gtest/gtest.h"
#include "Number.h"

TEST(Number, test_number_addition) {
	shaka::Number n1(10);
	shaka::Number n2(25);

	shaka::Number n3(n1 + n2);

	ASSERT_EQ(boost::get<Integer>(n3.get_value()), Integer(35));

}

TEST(Number, test_number_subtraction) {
	shaka::Number n1(20.5);
	shaka::Number n2(10);

	shaka::Number n3(n1 - n2);

	ASSERT_EQ(boost::get<Real>(n3.get_value()), Real(10.5));
}

TEST(Number, test_number_multiplication) {
	shaka::Number n1(2.0);
	shaka::Number n2(0.5);

	shaka::Number n3(n1 * n2);

	ASSERT_EQ(boost::get<Real>(n3.get_value()), Real(1.0));

}

TEST(Number, test_number_division) {
	shaka::Number n1(10);
	shaka::Number n2(2.0);

	shaka::Number n3(n1 / n2);

	ASSERT_EQ(boost::get<Real>(n3.get_value()), Real(5.0));
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

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}
