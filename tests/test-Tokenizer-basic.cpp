#include "gtest/gtest.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"


/// @brief Basic default constructor test
TEST(Tokenizer_basic, constructor) {
    shaka::Token(
        shaka::Token::Type::INVALID,
        ""
    );
}

TEST(Tokenizer_basic, comparison) {
    shaka::Token t1(
        shaka::Token::Type::NUMBER,
        "123"
    );

    shaka::Token t2(
        shaka::Token::Type::NUMBER,
        "123.234"
    );

    ASSERT_NE(t1, t2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
