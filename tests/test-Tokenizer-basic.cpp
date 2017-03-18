#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <deque>

#include <gtest/gtest.h>

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

TEST(Tokenizer_basic, list) {
    // Create the std::istream&
    std::stringstream ss("( \"asdf\" ) ; asdfasdfasdf\n)");
    // Setup the input stream with the Tokenizer
    shaka::Tokenizer tokenizer(ss);

    // Macro for convenience
    using Type = shaka::Token::Type;
    // Setup the sequence of tokens that is expected.
    std::vector<shaka::Token> expected {
        shaka::Token(Type::PAREN_START, "("),
        shaka::Token(Type::STRING, "asdf"),
        shaka::Token(Type::PAREN_END, ")"),
        shaka::Token(Type::PAREN_END, ")")
    };

    std::vector<shaka::Token> input;
    // Get and push tokens into the vector
    // while the tokenizer reads the entire stream.
    do {
        shaka::Token t = tokenizer.get();
        if (t != Type::END_OF_FILE) {
            input.push_back(t);
        } else {
            break;
        }
    } while (true);
  
    // Check that the tokens read is the same as the expected.
    for (unsigned i = 0; i < input.size(); ++i) {
        auto token = input[i];
        auto token2 = expected[i];

        ASSERT_EQ(token, token2);
    }
}





TEST(Tokenizer_basic, identifiers) {

    using Type = shaka::Token::Type;
    std::vector<shaka::Token> expected;
    std::vector<shaka::Token> input;

    std::stringstream ss1("(\t quantifier + / asdf \"qwer\"\n)");

    expected.clear(); 
    expected = {
        shaka::Token(Type::PAREN_START, "("),
        shaka::Token(Type::IDENTIFIER, "quantifier"),
        shaka::Token(Type::IDENTIFIER, "+"),
        shaka::Token(Type::IDENTIFIER, "/"),
        shaka::Token(Type::IDENTIFIER, "asdf"),
        shaka::Token(Type::STRING, "qwer"),
        shaka::Token(Type::PAREN_END, ")")
    };

    input.clear();
    shaka::Tokenizer tokenizer1(ss1);
    do {
        shaka::Token t = tokenizer1.get();
        if (t != Type::END_OF_FILE) {
            input.push_back(t);
        } else {
            break;
        }
    } while (true);
   
    for (unsigned i = 0; i < input.size(); ++i) {
        auto token = input[i];
        auto token2 = expected[i];

        ASSERT_EQ(token, token2);
    }
}

TEST(Tokenizer_basic, piped_identifier) {

    using Type = shaka::Token::Type;
    std::vector<shaka::Token> expected;
    std::vector<shaka::Token> input;
    std::stringstream ss2("|asdf\t\n$$|");

    expected.clear(); 
    expected = {
        shaka::Token(Type::IDENTIFIER, "asdf\t\n$$"),
    };

    input.clear();
    shaka::Tokenizer tokenizer2(ss2);
    do {
        shaka::Token t = tokenizer2.get();
        if (t != shaka::Token(Type::END_OF_FILE)) {
            input.push_back(t);
        } else {
            break;
        }
    } while (true);
   
    for (unsigned i = 0; i < input.size(); ++i) {
        auto token = input[i];
        auto token2 = expected[i];

        ASSERT_EQ(token, token2);
    }
}


TEST(Tokenizer_basic, comment_whitespace) {
    using Type = shaka::Token::Type;
    std::vector<shaka::Token> expected;
    std::vector<shaka::Token> input;
    std::stringstream ss3("#\\newline #\\t");

    expected.clear(); 
    expected = {
        shaka::Token(Type::CHARACTER, "\n"),
        shaka::Token(Type::CHARACTER, "t"),
    };

    input.clear();
    shaka::Tokenizer tokenizer3(ss3);
    do {
        shaka::Token t = tokenizer3.get();
        if (t != shaka::Token(Type::END_OF_FILE)) {
            input.push_back(t);
        } else {
            break;
        }
    } while (true);
   
    for (unsigned i = 0; i < input.size(); ++i) {
        auto token = input[i];
        auto token2 = expected[i];

        ASSERT_EQ(token, token2);
    }

}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
