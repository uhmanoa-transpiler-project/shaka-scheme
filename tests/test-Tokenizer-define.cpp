#include "gtest/gtest.h"
#include "Data.h"
#include "DataNode.h"
#include "IDataNode.h"
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

TEST(Tokenizer_define, define_fail) {

    std::stringstream ss("( define 123)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_FALSE( shaka::parser::rule::define(in, nullptr, interm) );
    std::cout << "interm: " << interm << std::endl;
}

TEST(Tokenizer_define, define_tree) {
    
    std::stringstream ss("(define x 1)");
    shaka::Tokenizer in(ss);
    std::string interm;

    std::shared_ptr<shaka::DataNode<shaka::Data>> root = 
        std::make_shared<shaka::DataNode<shaka::Data>>(shaka::MetaTag::DEFINE);

    ASSERT_TRUE( shaka::parser::rule::define(in, root, interm) );
    
    ASSERT_EQ( root->get_num_children(), 1 );
    auto child = root->get_child(0);

    ASSERT_EQ( child->get_num_children(), 2 );

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
