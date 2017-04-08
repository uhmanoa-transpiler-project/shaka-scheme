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

TEST(Parser_Rules, symbol_list_alpha) {
  std::stringstream ss("'(apple orange)");
  shaka::Tokenizer tk(ss);

  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::symbol_list<std::string>(tk, nullptr, interm));
}

TEST(Parser_Rules, symbol_list_num) {
  std::stringstream ss("'(7 8 9)");
  shaka::Tokenizer tk(ss);

  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::symbol_list<std::string>(tk, nullptr, interm));
}

TEST(Parser_Rules, symbol_list_mixed) {
  std::stringstream ss("'(4 score n 7 yrs)");
  shaka::Tokenizer tk(ss);

  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::symbol_list<std::string>(tk, nullptr, interm));
}

TEST(Parser_Rules, proc_quote_alpha) {
  std::stringstream ss("(quote square circle triangle)");
  shaka::Tokenizer tk(ss);

  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::proc_quote<std::string>(tk, nullptr, interm));
}

TEST(Parser_Rules, proc_quote_num) {
  std::stringstream ss("(quote 9001 13 3)");
  shaka::Tokenizer tk(ss);

  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::proc_quote<std::string>(tk, nullptr, interm));
}

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

TEST(Tokenizer_list, proc_tree) {

    std::stringstream ss("(quote x 1)");
    shaka::Tokenizer in(ss);
    std::string interm;

    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    ASSERT_TRUE( shaka::parser::rule::proc_quote(in, root, interm) );

    ASSERT_EQ( root->get_num_children(), 1);

    auto lol = root->get_child(0);

    ASSERT_EQ( lol->get_num_children(), 2);

}

TEST(Tokenizer_list, symbol_tree) {

    std::stringstream ss("'(x 1)");
    shaka::Tokenizer in(ss);
    std::string interm;

    std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
    std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

    ASSERT_TRUE( shaka::parser::rule::symbol_list(in, root, interm) );

    ASSERT_EQ( root->get_num_children(), 1);

    auto lol = root->get_child(0);

    ASSERT_EQ( lol->get_num_children(), 2);

    // ASSERT_EQ(shaka::Number(1), shaka::Number(lol->get_child(1)->get_data()));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
