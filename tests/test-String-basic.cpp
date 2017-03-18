
/*
#include <gtest/gtest.h>

TEST(Stringasdf, empty_string_constructor){ }

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
	for(int i =5; i!= 10; i++)
		ASSERT_EQ(a.getString()[i], 'a');	

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
	a.string_copy(b, 3);
	c.substring(a, 3, 5);
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

*/

#include <gtest/gtest.h>
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
