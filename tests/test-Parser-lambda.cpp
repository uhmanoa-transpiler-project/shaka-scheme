#include "gtest/gtest.h"
#include "Data.h"
#include "DataNode.h"
#include "IDataNode.h"
#include "Environment.h"
#include "Evaluator.h"

#include "parser/Tokenizer.h"
#include "parser/Token.h"
#include "parser/rule_lambda.h"
#include "parser/rule_lambda_impl.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/// @brief Basic default constructor test
TEST(Parser_lambda, token_constructor) {
    shaka::Token(
        shaka::Token::Type::INVALID,
        "(lambda (x) x)"
    );
}

/// @brief Assert that two tokens are equal
TEST(Parser_lambda, tokenizer_test) {
    // Create a stringstream and give it to the Tokenizer
    std::stringstream ss("(lambda (x) x)");
    shaka::Tokenizer tk(ss);

    shaka::Token tok1 = tk.get();
    shaka::Token tok2(shaka::Token::Type::PAREN_START, "(");

    ASSERT_EQ(tok1, tok2);
}

/// @brief Assert that rule_define can parse the base 
/// of (define asdf 1)
TEST(Parser_lambda, lambda_base_case) {

    std::stringstream ss("(lambda (x) x)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::lambda(in, nullptr, interm) );
    std::cout << "interm: " << interm << std::endl;
}
/*
/// @brief Asser that rule_define can parse a slightly
/// more complicated version of define using extra whitespace
TEST(Parser_lambda, define_number) {

    std::stringstream ss(" (   define \n true \n1 \n )");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::define(in, nullptr, interm) );
    std::cout << "interm: " << interm << std::endl;
}

/// @brief Test that rule_define can parse a boolean as the 
/// expression
TEST(Parser_lambda, define_bool) {
    
    std::stringstream ss("(define true #true)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::define(in, nullptr, interm) );
    std::cout << "interm: " << interm << std::endl;
}

TEST(Parser_lambda, define_fail) {

    std::stringstream ss("( define 123)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_FALSE( shaka::parser::rule::define(in, nullptr, interm) );
    std::cout << "interm: " << interm << std::endl;
}

////////////////////////////////
//        TREE TESTS          //
////////////////////////////////

using Data = shaka::Data;
using IDataTree = shaka::IDataNode<Data>;
using DataTree  = shaka::DataNode<Data>;
using Environment = shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Parser_lambda, define_tree) {
    
    std::stringstream ss("(define x 1)");
    shaka::Tokenizer in(ss);
    std::string interm;

    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    ASSERT_TRUE( shaka::parser::rule::define(in, root, interm) );

    shaka::Evaluator evaluator(root->get_child(0), env);
    evaluator.evaluate(shaka::eval::Define());

    ASSERT_EQ( root->get_num_children(), 1 );
    auto child = root->get_child(0);
    ASSERT_EQ( child->get_num_children(), 2 );
    ASSERT_EQ(typeid(shaka::Number), env->get_value(shaka::Symbol("x"))->get_data()->type());
    ASSERT_EQ(shaka::Number(1), shaka::get<shaka::Number>(*env->get_value(shaka::Symbol("x"))->get_data()));
}
*/
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
