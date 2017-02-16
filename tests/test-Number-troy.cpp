#include "gtest/gtest.h"
#include "Number.h"

TEST(Number, test_number_addition) {
	shaka::Number n1(Integer(10));
	shaka::Number n2(Integer(25));

	shaka::Number n3(n1 + n2);

	ASSERT_EQ(boost::get<Integer>(n3.get_value()), Integer(35));

}

TEST(Number, test_number_subtraction) {
	shaka::Number n1(Real(20.5));
	shaka::Number n2(Integer(10));

	shaka::Number n3(n1 - n2);

	ASSERT_EQ(boost::get<Real>(n3.get_value()), Real(10.5));
}


int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}
