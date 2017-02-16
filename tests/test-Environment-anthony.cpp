#include "gtest/gtest.h"
#include "Environment.h"

TEST(Environment, get_parent){
	shaka::Environment a(nullptr);
	ASSERT_EQ(a.get_parent(), nullptr);
	
}



int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}











