#include "gtest/gtest.h"
#include "Data.h"
#include "DataNode.h"
#include "IDataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Define.h"

#include "parser/Tokenizer.h"
#include "parser/Token.h"
#include "parser/rule_list.h"
#include "parser/rule_list_impl.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <cctype>

// quote literal with alpha IDs
TEST(Parser_Rules, symbol_list_alpha) {
  std::stringstream ss("'(apple orange)");
  shaka::Tokenizer tk(ss);
  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::symbol_list<std::string>(tk, nullptr, interm));
}

// quote literal with numbers
TEST(Parser_Rules, symbol_list_num) {
  std::stringstream ss("'(7 8 9)");
  shaka::Tokenizer tk(ss);
  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::symbol_list<std::string>(tk, nullptr, interm));
}

// quote literal with mix of numbers and alpha IDs
TEST(Parser_Rules, symbol_list_mixed) {
  std::stringstream ss("'(4 score n 7 yrs)");
  shaka::Tokenizer tk(ss);
  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::symbol_list<std::string>(tk, nullptr, interm));
}

// quote procedure with alpha IDs
TEST(Parser_Rules, proc_quote_alpha) {
  std::stringstream ss("(quote square circle triangle)");
  shaka::Tokenizer tk(ss);
  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::proc_quote<std::string>(tk, nullptr, interm));
}

// quote procedure with number
TEST(Parser_Rules, proc_quote_num) {
  std::stringstream ss("(quote 9001 13 3)");
  shaka::Tokenizer tk(ss);
  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::proc_quote<std::string>(tk, nullptr, interm));
}

// quote procedure with mix of numbers and alpha IDs
TEST(Parser_Rules, proc_quote_mixed) {
  std::stringstream ss("(quote c7ay 10 l35 b1)");
  shaka::Tokenizer tk(ss);
  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::proc_quote<std::string>(tk, nullptr, interm));
}

using Data = shaka::Data;
using IDataTree = shaka::IDataNode<Data>;
using DataTree  = shaka::DataNode<Data>;
using Environment = shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

// quote procedure onto tree
TEST(Tokenizer_list, proc_tree) {
    std::stringstream ss("(quote x 13)");
    shaka::Tokenizer in(ss);
    std::string interm;

    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    ASSERT_TRUE(shaka::parser::rule::proc_quote(in, root, interm) );
    ASSERT_EQ(root->get_num_children(), 1);
    auto lol = root->get_child(0);
    ASSERT_EQ(lol->get_num_children(), 2);
    ASSERT_EQ(shaka::get<shaka::Number>(*lol->get_child(1)->get_data()), shaka::Number(13));
    ASSERT_EQ(shaka::get<shaka::Symbol>(*lol->get_child(0)->get_data()), shaka::Symbol("x"));
}

// quote literal onto tree
TEST(Tokenizer_list, symbol_tree) {
    std::stringstream ss("'(x 13)");
    shaka::Tokenizer in(ss);
    std::string interm;

    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    ASSERT_TRUE(shaka::parser::rule::symbol_list(in, root, interm));
    ASSERT_EQ(root->get_num_children(), 1);
    auto lol = root->get_child(0);
    ASSERT_EQ(lol->get_num_children(), 2);
    ASSERT_EQ(shaka::get<shaka::Number>(*lol->get_child(1)->get_data()), shaka::Number(13));
    ASSERT_EQ(shaka::get<shaka::Symbol>(*lol->get_child(0)->get_data()), shaka::Symbol("x"));
}

// quote procedure number only onto tree
TEST(Tokenizer_list, proc_tree_more_num) {
  std::stringstream ss("(quote 18 5 67 4 3)");
  shaka::Tokenizer in(ss);
  std::string interm;

  std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
  std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

  ASSERT_TRUE(shaka::parser::rule::proc_quote(in, root, interm));
  ASSERT_EQ(root->get_num_children(), 1);
  auto kid = root->get_child(0);
  ASSERT_EQ(kid->get_num_children(), 5);

  ASSERT_EQ(shaka::get<shaka::Number>(*kid->get_child(0)->get_data()), shaka::Number(18));
  ASSERT_EQ(shaka::get<shaka::Number>(*kid->get_child(1)->get_data()), shaka::Number(5));
  ASSERT_EQ(shaka::get<shaka::Number>(*kid->get_child(2)->get_data()), shaka::Number(67));
  ASSERT_EQ(shaka::get<shaka::Number>(*kid->get_child(3)->get_data()), shaka::Number(4));
  ASSERT_EQ(shaka::get<shaka::Number>(*kid->get_child(4)->get_data()), shaka::Number(3));
}

// quote procedure alpha IDs only onto tree
TEST(Tokenizer_list, proc_quote_more_alpha) {
  std::stringstream ss("(quote fee fi fo fum)");
  shaka::Tokenizer in(ss);
  std::string interm;

  std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
  std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

  ASSERT_TRUE(shaka::parser::rule::proc_quote(in, root, interm));
  ASSERT_EQ(root->get_num_children(), 1);
  auto kid = root->get_child(0);
  ASSERT_EQ(kid->get_num_children(), 4);

  ASSERT_EQ(shaka::get<shaka::Symbol>(*kid->get_child(0)->get_data()), shaka::Symbol("fee"));
  ASSERT_EQ(shaka::get<shaka::Symbol>(*kid->get_child(1)->get_data()), shaka::Symbol("fi"));
  ASSERT_EQ(shaka::get<shaka::Symbol>(*kid->get_child(2)->get_data()), shaka::Symbol("fo"));
  ASSERT_EQ(shaka::get<shaka::Symbol>(*kid->get_child(3)->get_data()), shaka::Symbol("fum"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
