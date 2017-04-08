#include "gtest/gtest.h"
#include "Boolean.h" 

TEST(Boolean, a_Boolean){
	shaka::Boolean n1(1 == 1 );
	shaka::Boolean n2(1 > 2 );

	ASSERT_EQ(n1 == n2, false);
}

TEST(Boolean, check_equal_Boolean){
	shaka::Boolean n1(1 == 1 );
	shaka::Boolean n2(1 < 2 );

	ASSERT_EQ(n1 == n2, true);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}