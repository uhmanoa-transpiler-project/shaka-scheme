#include "gtest/gtest.h"
#include "Integer.h"

TEST(Integer, add_integer_and_rational) {
	shaka::Integer i(5);
	shaka::Rational r(1, 2);

	shaka::Rational r2(i + r);

	ASSERT_EQ(r2.get_numerator(), static_cast<int>(11));
	ASSERT_EQ(r2.get_denominator(), static_cast<int>(2));

}

TEST(Integer, sub_integer_and_rational) {
	shaka::Integer i(3);
	shaka::Rational r(1, 2);

	shaka::Rational r2(i - r);

	ASSERT_EQ(r2.get_numerator(), static_cast<int>(5));
	ASSERT_EQ(r2.get_denominator(), static_cast<int>(2));
}

TEST(Integer, mul_integer_and_rational) {
	shaka::Integer i(5);
	shaka::Rational r(1, 2);

	shaka::Rational r2(r * i); 

	ASSERT_EQ(r2.get_numerator(), static_cast<int>(5));
	ASSERT_EQ(r2.get_denominator(), static_cast<int>(2));
}

TEST(Integer, div_integer_and_rational) {
	shaka::Integer i(10);
	shaka::Rational r(1, 2);
	shaka::Rational r2(r / i); 
    
	ASSERT_EQ(r2.get_numerator(), static_cast<int>(1));
	ASSERT_EQ(r2.get_denominator(), static_cast<int>(20));

}



int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
