#include "gtest/gtest.h"
#include "Data.h"
#include "DataNode.h"
#include "IDataNode.h"
#include "Environment.h"
#include "Evaluator.h"

#include "parser/Tokenizer.h"
#include "parser/Token.h"
#include "parser/rule_expression_impl.h"

#include <iostream>
#include <sstream>
#include <string>

/// @brief Basic default constructor test
TEST(Parser_expression, token_constructor) {
    shaka::Token(
        shaka::Token::Type::INVALID,
        "hello"
    );
}

/// @brief Assert that two tokens are equal
TEST(Parser_expression, tokenizer_test) {
    // Create a stringstream and give it to the Tokenizer
    std::stringstream ss("()");
    shaka::Tokenizer tk(ss);

    shaka::Token tok1 = tk.get();
    shaka::Token tok2(shaka::Token::Type::PAREN_START, "(");

    ASSERT_EQ(tok1, tok2);
}

/// @brief Assert that rule_expression can parse through
//   a very simple expression case
TEST(Parser_expression, expression_simple_identifier) {

    std::stringstream ss("hello");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::expression(in, nullptr, interm) );
    ASSERT_EQ(ss.str(), interm);
}

/// @brief Assert that rule_expression can parse through
//   a simple expression case
TEST(Parser_expression, expression_as_bool) {

    std::stringstream ss("#t");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::expression(in, nullptr, interm) );
    ASSERT_EQ(ss.str(), interm);
}

/// @brief Assert that rule_expression can parse through
//   a simple expression case
TEST(Parser_expression, expression_as_bool2) {

    std::stringstream ss("#false");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::expression(in, nullptr, interm) );
    ASSERT_EQ("#f", interm);
}

// Extra case
TEST(Parser_expression, expression_as_lambda) {

    std::stringstream ss("(lambda (x y.z) 400)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::expression(in, nullptr, interm) );
    ASSERT_EQ(ss.str(), interm);
}

/// @brief Assert that rule_expression can parse the same
//   simple expression case as in above with extra whitespace.
TEST(Parser_expression, expression_as_lambda_with_whitespace) {

    std::stringstream ss(" (   lambda \n (   x) \nx \n )");
    shaka::Tokenizer in(ss);
    std::string result = "(lambda (x) x)";
    std::string interm;

    EXPECT_TRUE( shaka::parser::rule::expression(in, nullptr, interm) );
    ASSERT_EQ(result, interm);
}

/// @brief Test that rule_expression can parse
//   a expression that contains a define
TEST(Parser_expression, expression_as_lambda_complicated) {
    
    std::stringstream ss("(lambda (x y z) (define a #t) 100)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::expression(in, nullptr, interm) );
    ASSERT_EQ(ss.str(), interm);
}

TEST(Parser_expression, expression_fail_on_different_rule) {

    std::stringstream ss("(define x 1)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_FALSE( shaka::parser::rule::expression(in, nullptr, interm) );
}

TEST(Parser_expression, expression_fail_on_incomplete_expression) {

    std::stringstream ss("(lambda (xx))");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_FALSE( shaka::parser::rule::expression(in, nullptr, interm) );
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

TEST(Parser_expression, basic_expression_tree) {
    
    std::stringstream ss("(expression x 1)");
    shaka::Tokenizer in(ss);
    std::string interm;

    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    ASSERT_TRUE( shaka::parser::rule::expression(in, root, interm) );

    shaka::Evaluator evaluator(root->get_child(0), env);
    evaluator.evaluate(shaka::eval::expression());

    ASSERT_EQ( root->get_num_children(), 1 );
    auto expressionNode = root->get_child(0);
    ASSERT_EQ( expressionNode->get_num_children(), 2 );
    auto argsNode = expressionNode->get_child(0);
    auto bodyNode = expressionNode->get_child(1);
    ASSERT_EQ( argsNode->get_num_children(), 1 );
    ASSERT_EQ( argsNode->get_num_children(), 1 );
}
*/

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
