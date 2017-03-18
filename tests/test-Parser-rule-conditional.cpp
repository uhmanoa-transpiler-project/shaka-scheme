#include "gtest/gtest.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"
#include "parser/rule-conditional.h"

#include <sstream>
#include <vector>

TEST(Parser_Rules, conditional) {
    // Create a stringstream and give it to the Tokenizer
    std::stringstream ss("(if (> 3 2) #t #f)");
    shaka::Tokenizer tk(ss);
	
    std::string interm;

    ASSERT_TRUE(shaka::parser::rule::conditional<std::string>(tk, nullptr, interm));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
