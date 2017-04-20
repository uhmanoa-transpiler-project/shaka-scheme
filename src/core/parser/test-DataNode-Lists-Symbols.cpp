#include "gtest/gtest.h"

#include "core/base/DataNode.h"

#include <sstream>

using namespace shaka;

//Constructor for symbols
TEST(Symbols, constructor) {
	DataNode s0(Symbol("a"));
	std::cout << "Symbol:" << s0 << std::endl;
	ASSERT_TRUE(s0.is_symbol());
}

//Testing cons() with symbols
TEST(Symbols, cons) {
	DataNode s1(shaka::Symbol("a"));
	DataNode s2(shaka::Symbol("b"));
	DataNode s3 = DataNode::cons(s2, s1);

	ASSERT_FALSE(s3.is_null());
	ASSERT_TRUE(s3.is_pair());
	
	//Print out list
	std::cout << "List:" << s3 << std::endl;
	
}

//Testing car() and cdr() with symbols
TEST(Symbols, car_cdr) {
	//Create a list of symbols
	DataNode s0({Symbol("a")}, {Symbol("b")});
	ASSERT_TRUE(s0.is_pair());
	ASSERT_FALSE(s0.is_null());
	ASSERT_FALSE(s0.is_list());

	//car()
	DataNode head = *s0.car();
	ASSERT_EQ(head, DataNode(Symbol("a")));
	ASSERT_FALSE(head.is_pair());
	ASSERT_FALSE(head.is_null());
	ASSERT_FALSE(head.is_list());
	
	//cdr() this gets the rest of the list
	DataNode tail = *s0.cdr();
	ASSERT_EQ(tail, DataNode(Symbol("b")));
	ASSERT_FALSE(tail.is_pair());
	ASSERT_FALSE(tail.is_null());
	ASSERT_FALSE(tail.is_list());

	//Print list
	std::cout << "Head:" << head 
		  << "\nTail:" << tail 
		  << "\nList:" << s0 << std::endl;
}

//Testing list() with symbols
TEST(Symbols, list) {
	//Create a list of symbols
	DataNode List_symbols = DataNode::list(Symbol("a"), Symbol("b"), Symbol("c"));

	//Check if it is a list
	ASSERT_EQ(List_symbols.is_list(), true);

	//Grab every element in the list	
	DataNode el1 = *List_symbols.car();
	DataNode el1_tail = *List_symbols.cdr();
	DataNode el2 = *el1_tail.car();
	DataNode el2_tail = *el1_tail.cdr();
	DataNode el3 = *el2_tail.car();

	//Print the elements
	std::cout << "Element 1: " << el1
		  << "\nElement 2: " << el2
		  << "\nElement 3: " << el3 << std::endl;
	
	//Check if they're equal 
	ASSERT_EQ(el1, DataNode(Symbol("a")));
	ASSERT_EQ(el2, DataNode(Symbol("b")));
	ASSERT_EQ(el3, DataNode(Symbol("c")));

	//Print the list	
	std::cout << "List:" << List_symbols << std::endl;
}	


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
