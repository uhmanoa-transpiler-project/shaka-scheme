#include "gtest/gtest.h"
#include "parser/Tokenizer.h"
#include "parser/Token.h"
#include "parser/rule_define.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/// @brief Basic default constructor test
TEST(Tokenizer_define, token_constructor) {
    shaka::Token(
        shaka::Token::Type::INVALID,
        "(define asdf 1)"
    );
}

TEST(Tokenizer_define, tokenizer_test) {
    // Create a stringstream and give it to the Tokenizer
    std::stringstream ss("( define\nasdf\t1    )");
    shaka::Tokenizer tk(ss);

    shaka::Token tok1 = tk.get();
    shaka::Token tok2(shaka::Token::Type::PAREN_START, "(");

    ASSERT_EQ(tok1, tok2);
}

TEST(Tokenizer_define, define_return) {

    std::stringstream ss("( define asdf 1 )");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::define(in, nullptr, interm) );
    std::cout << "interm: " << interm << std::endl;
}

TEST(Tokenizer_define, define_number) {

    std::stringstream ss(" (   define \n true \n1 \n )");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::define(in, nullptr, interm) );
    std::cout << "interm: " << interm << std::endl;
}
TEST(Tokenizer_define, define_bool) {
    
    std::stringstream ss("(define true #true)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::define(in, nullptr, interm) );
    std::cout << "interm: " << interm << std::endl;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
