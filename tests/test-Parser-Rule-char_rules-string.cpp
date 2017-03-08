#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "parser/char_rules_string.h"

TEST(Parser_char_rules, alpha) {
	std::stringstream ss("z");
	std::string interm;

	//Assert z is an alpha char
	ASSERT_TRUE( 
		shaka::parser::rule::alpha<std::string>(ss, nullptr, interm)
	);
}

TEST(Parser_char_rules, alpha_string) {
	std::stringstream ss("zeta");
	std::string interm;

	while(auto good = 
		shaka::parser::rule::alpha<std::string>(ss, nullptr, interm)
	     ) { }
	
	//Assert zeta is a string
	ASSERT_EQ(interm, "zeta");

	//ASSERT_TRUE( 
	//	shaka::parser::rule::alpha<std::string>(ss, nullptr, interm)
	//);
}

TEST(Parser_char_rules, digit) {

    {
        std::stringstream iss("1");
        std::string temp;

        // Assert that 1 is a digit
        ASSERT_TRUE(
            shaka::parser::rule::digit<std::string>(iss, nullptr, temp)
        );
    }


    {
        std::stringstream iss("0123456789");
        std::string temp;

        // Read until the next character is NOT a digit.
        while (auto good =  
            shaka::parser::rule::digit<std::string>(
                iss, nullptr, temp
            )
        ) {}

        // Make sure that the sum of the numbers
        ASSERT_EQ(std::stoi(temp), std::stoi("0123456789"));
    }
}

TEST(Parser_char_rules, match_char) {
    std::stringstream iss ("(");
    std::string temp;

    auto b = shaka::parser::rule::match_char
        <std::string, '('>(iss, nullptr, temp);

    ASSERT_EQ(
        true,
        b
    );
}

TEST(Parser_char_rules, match_string) {
	std::stringstream ss("\"");
	std::string interm;

	ASSERT_TRUE(
		shaka::parser::rule::match_string<std::string>(ss, nullptr, interm)
	);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
