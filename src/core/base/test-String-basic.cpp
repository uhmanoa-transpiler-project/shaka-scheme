#include "core/base/String.h"
#include <gtest/gtest.h>

TEST(String, Single_element_constructor){
	int size = 5;
	shaka::String a(size, 'a');
	char b = a.string_ref(0);

	ASSERT_EQ(b=='a', true);

}
TEST(String, copy_constructor){
	int size = 5;
	shaka::String a(size, 'b');
	shaka::String c(a);
	ASSERT_TRUE(c==a);
}

TEST(String, move_constructor) {
    shaka::String abc("asdf");
    abc = std::move(abc);
    ASSERT_EQ(abc, shaka::String("asdf"));
}

TEST(String, copy_constructor_two){
	int size = 5;
	int size1 = 3;
	shaka::String a(size, 'b');
	shaka::String c(a, 2);
	shaka::String d(size1, 'b');	
	ASSERT_TRUE(c==d);
	
}
TEST(String, substring_constructor){
	int size = 5;
	shaka::String a(size, 'a');
	shaka::String b(a, 1, 2);
	shaka::String c(b);
	ASSERT_TRUE(b==c); 
}
TEST(String, get_length){
	int size = 5;
	shaka::String a(size, 'a');
	ASSERT_EQ(a.string_length(), 5);
}
TEST(String, string_ref){
	int size = 5;
	shaka::String a(size, 'b');
	ASSERT_EQ(a.string_ref(2), 'b');
}
TEST(String, string_set){
	int size = 5;
	shaka::String a(size, 'b');
	a.string_set(3, 'a');
	ASSERT_EQ(a.string_ref(3), 'a');
}
TEST(String, string_append){
	int size = 5;
	shaka::String a(size, 'c');
	shaka::String b(size, 'a');
        a.string_append(b);
	for(int i =5; i!= 10; i++){
		ASSERT_EQ(a.getString()[i], 'a');	
	}
}
TEST(String, string_copy_one){
	int size = 5;
	shaka::String a(size, 'a');
	shaka::String b(size , 'b');
	a.string_copy(b);
	ASSERT_TRUE(a==b);	
}
TEST(String, string_copy_two){
	int size = 5;
	int size1 =2;
	shaka::String a(size, 'a');
	shaka::String b(size, 'b');
	shaka::String c(size1);
	shaka::String d(size1, 'b');
	a.string_copy(b, 2, 4);
	c.substring(a, 0, 2);
	ASSERT_TRUE(c==d);
}

TEST(String, getString){
	int size = 5;
	shaka::String a(size, 'a');
	std::vector<char> test = a.getString();
	ASSERT_EQ(test, a.getString());

}
TEST(String, string_fill){
	int size = 5;
	shaka::String a(size, 'a');
	shaka::String b(size, 'b');
	a.string_fill('b');
	ASSERT_TRUE(a==b);
}
TEST(String, string_fill_one){
	int size = 5;
	shaka::String a(size, 'a');
	shaka::String b(size, 'b');
	shaka::String c(size);
	a.string_fill('b', 2);
	for(int i=2; i<size; i++){
	  ASSERT_TRUE(a.string_ref(i)=='b');
	}
}
TEST(String, string_fill_two){
	int size = 5;
	shaka::String a(size, 'a');
	a.string_fill('b', 1, 3);
	for(int i=1; i<4; i++){
	ASSERT_TRUE(a.string_ref(i)=='b');
	}
}


TEST(String, string_upcase){
	int size = 5;
	shaka::String a(size, 'a');
	shaka::String b(size, 'A');
	a.string_upcase();
	ASSERT_TRUE(b==a);
}
TEST(String, string_downcasecase){
	int size = 5;
	shaka::String a(size, 'A');
	shaka::String b(size, 'a');
	a.string_downcase();
	ASSERT_TRUE(b==a);
}


#include <gtest/gtest.h>
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
