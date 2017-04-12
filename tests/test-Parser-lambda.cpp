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

/// @brief Assert that rule_lambda can parse through
//   a very simple lambda case
TEST(Parser_lambda, lambda_super_simple) {

    std::stringstream ss("(lambda x 1)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::lambda(in, nullptr, interm) );
    ASSERT_EQ(ss.str(), interm);
}

/// @brief Assert that rule_lambda can parse through
//   a simple lambda case
TEST(Parser_lambda, lambda_base_case) {

    std::stringstream ss("(lambda (x) x)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::lambda(in, nullptr, interm) );
    ASSERT_EQ(ss.str(), interm);
}
/// @brief Assert that rule_lambda can parse the same
//   simple lambda case as in above with extra whitespace.
TEST(Parser_lambda, base_case_with_whitespace) {

    std::stringstream ss(" (   lambda \n (   x) \nx \n )");
    shaka::Tokenizer in(ss);
    std::string result = "(lambda (x) x)";
    std::string interm;

    EXPECT_TRUE( shaka::parser::rule::lambda(in, nullptr, interm) );
    ASSERT_EQ(result, interm);
}

/// @brief Test that rule_lambda can parse
//   a lambda that contains a define
TEST(Parser_lambda, lambda_complicated) {
    
    std::stringstream ss("(lambda (x y z) (define a #t) 100)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::lambda(in, nullptr, interm) );
    ASSERT_EQ(ss.str(), interm);
}

TEST(Parser_lambda, lambda_fail_on_different_rule) {

    std::stringstream ss("(define x 1)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_FALSE( shaka::parser::rule::lambda(in, nullptr, interm) );
}

TEST(Parser_lambda, lambda_fail_on_incomplete_lambda) {

    std::stringstream ss("(lambda (xx))");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_FALSE( shaka::parser::rule::lambda(in, nullptr, interm) );
    ASSERT_EQ("(lambda (xx) ", interm);
}

////////////////////////////////
//        TREE TESTS          //
////////////////////////////////
/*

using Data = shaka::Data;
using IDataTree = shaka::IDataNode<Data>;
using DataTree  = shaka::DataNode<Data>;
using Environment = shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Parser_lambda, basic_lambda_tree) {
    
    std::stringstream ss("(lambda x 1)");
    shaka::Tokenizer in(ss);
    std::string interm;

    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    ASSERT_TRUE( shaka::parser::rule::lambda(in, root, interm) );

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
