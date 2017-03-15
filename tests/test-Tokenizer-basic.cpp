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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
