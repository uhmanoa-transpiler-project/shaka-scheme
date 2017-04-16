#include <gtest/gtest.h>

#include "core/base/DataNode.h"
#include "core/parser/Tokenizer.h"
#include "core/parser/list.h"

#include <sstream>
#include <iostream>

TEST(Parse_list, compiles) {
    ASSERT_TRUE(true);
}

TEST(Parse_list, tokenizer) {
    std::stringstream ss("(define x 1)");
    shaka::Tokenizer in(ss);

    shaka::Token token = in.get();
    ASSERT_EQ(token.type, shaka::Token::Type::PAREN_START);
}

TEST(Parse_list, list_simple_case1) {
    std::stringstream ss("(define x 1)");
    std::stringstream out;
    shaka::Tokenizer in(ss);

    shaka::DataNode node = shaka::parser::list(in);
    out << node;
    ASSERT_EQ(ss.str(), out.str());
}

TEST(Parse_list, list_simple_case2) {
    std::stringstream ss("(define (x y z) 5 30)");
    std::stringstream out;
    shaka::Tokenizer in(ss);

    shaka::DataNode node = shaka::parser::list(in);
    out << node;
    ASSERT_EQ(ss.str(), out.str());
}

TEST(Parse_list, list_simple_case3) {
    std::stringstream ss("(quote (1 2 3))");
    std::stringstream out;
    shaka::Tokenizer in(ss);

    shaka::DataNode node = shaka::parser::list(in);
    out << node;
    ASSERT_EQ(ss.str(), out.str());
}

TEST(Parse_list, list_simple_case4) {
    std::stringstream ss("('(1 2 3))");
    std::stringstream out;
    std::string ans = "(quote (1 2 3))";
    shaka::Tokenizer in(ss);

    shaka::DataNode node = shaka::parser::list(in);
    out << node;
    ASSERT_EQ(ans, out.str());
}

TEST(Parse_list, list_simple_case5) {
    std::stringstream ss("(+ 1 2)");
    std::stringstream out;
    shaka::Tokenizer in(ss);

    shaka::DataNode node = shaka::parser::list(in);
    out << node;
    ASSERT_EQ(ss.str(), out.str());
}

TEST(Parse_list, list_simple_case6) {
    std::stringstream ss("(1 . 2)");
    std::stringstream out;
    shaka::Tokenizer in(ss);

    shaka::DataNode node = shaka::parser::list(in);
    out << node;
    ASSERT_EQ(ss.str(), out.str());
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
