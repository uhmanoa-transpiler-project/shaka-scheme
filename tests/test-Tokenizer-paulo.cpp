#include <sstream>
#include "gtest/gtest.h"

#include "parser/Tokenizer.h"
#include "parser/Token.h"

TEST(token_base, constructor) {
    shaka::Token token0(shaka::Token::Type::IDENTIFIER);
    shaka::Token token1(shaka::Token::Type::IDENTIFIER);

    ASSERT_TRUE(true);
}

TEST(token_base, equality_empty_string) {
    shaka::Token token0(shaka::Token::Type::IDENTIFIER);
    shaka::Token token1(shaka::Token::Type::IDENTIFIER);

    ASSERT_TRUE(token0 == token1);
    ASSERT_FALSE(token0 != token1);
}


TEST(token_base, equality_different_string) {
    shaka::Token token0(shaka::Token::Type::IDENTIFIER, "123");
    shaka::Token token1(shaka::Token::Type::IDENTIFIER, "abc");

    ASSERT_FALSE(token0 == token1);
    ASSERT_TRUE(token0 != token1);
}

TEST(tokenizer, constructor) {
    std::stringstream ss("#f");
    shaka::Tokenizer tokenizer(ss);
    shaka::Token token = tokenizer.get();

    ASSERT_TRUE(true);
}

TEST(tokenizer, get) {
    std::stringstream ss("#f");
    shaka::Tokenizer tokenizer(ss);
    shaka::Token token0 = tokenizer.get();
    shaka::Token token1(shaka::Token::Type::BOOLEAN_FALSE, "#f");

    ASSERT_TRUE( token0 == token1 );
    ASSERT_EQ( token0, token1 );
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
