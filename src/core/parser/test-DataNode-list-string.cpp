#include "gtest/gtest.h"

#include "core/base/DataNode.h"

#include <iostream>
#include <sstream>

using namespace shaka;

TEST(String,constructor){
	DataNode d0(String("Sample"));
	std::cout << d0 << std::endl;
	ASSERT_TRUE(d0.is_string());
}

TEST(String,cons){
	DataNode d0(String("Hello"));
	DataNode d1(String("World"));
	DataNode d2 = DataNode::cons(d0,d1);
	std::cout << d2 << std::endl; 
	ASSERT_TRUE(d2.is_pair());
}

TEST(String,car_cdr){
	DataNode d0({String("abc")},{String("def")});

	std::cout << d0 << std::endl;

	DataNode head = *d0.car();
	std::cout << "head = " << head << std::endl;
	ASSERT_EQ(head, DataNode(String("abc")));
	ASSERT_FALSE(head.is_pair());
	ASSERT_FALSE(head.is_null());
	ASSERT_FALSE(head.is_list());

	DataNode tail = *d0.cdr();
	std::cout << "tail = " << tail << std::endl;
	ASSERT_EQ(tail, DataNode(String("def")));
	ASSERT_FALSE(tail.is_pair());
	ASSERT_FALSE(tail.is_null());
	ASSERT_FALSE(tail.is_list());

}

TEST(String,list){
	std::stringstream ss;
	DataNode d0 = DataNode::list(String("abc"),String("def"),String("ghi"));
	std::cout << d0 << std::endl;
	ss << d0;
	ASSERT_EQ(ss.str(),std::string("(\"abc\" \"def\" \"ghi\")"));
}

int main(int argc,char** argv){
	::testing::InitGoogleTest(&argc,argv);

	return RUN_ALL_TESTS();
}
