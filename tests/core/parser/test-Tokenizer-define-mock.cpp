#include "gtest/gtest.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"

#include <sstream>
#include <vector>

/// @brief Basic default constructor test
TEST(Tokenizer_define_mock, constructor) {
    shaka::Token(
        shaka::Token::Type::INVALID,
        "(define asdf 1)"
    );
}

TEST(Tokenizer_define_mock, parse) {
    // Create a stringstream and give it to the Tokenizer
    std::stringstream ss("( define\nasdf\t1    )");
    shaka::Tokenizer tk(ss);

    using shaka::Token;

    // Create a vector or sequence of tokens that it should match.
    std::vector<shaka::Token> v = {
        {Token::Type::PAREN_START, "("},
        {Token::Type::IDENTIFIER, "define"},
        {Token::Type::IDENTIFIER, "asdf"},
        {Token::Type::NUMBER, "1"},
        {Token::Type::PAREN_END, ")"}
    };

    // Make sure that each read in token matches before the end of file.
    int index = 0;
    for (auto t = tk.get(); t.type != shaka::Token::Type::END_OF_FILE; t = tk.get()) {
        ASSERT_EQ(v[index], t);
        ++index;
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
