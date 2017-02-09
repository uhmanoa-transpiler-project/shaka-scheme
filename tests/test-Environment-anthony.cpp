#include "gtest/gtest.h"
#include "Environment.h"

TEST(Environment, getParent){
	shaka::Environment a;
	ASSERT_EQ(a.getParentPtr(), nullptr);
	
}



int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}











