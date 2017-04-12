#include "gtest/gtest.h"
#include "Data.h"
#include "DataNode.h"
#include "IDataNode.h"
#include "Environment.h"
#include "Evaluator.h"
#include "Eval_Define.h"

#include "parser/Tokenizer.h"
#include "parser/Token.h"
#include "parser/rule_expression.h"
#include "parser/rule_expression_impl.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// identifier alpha ID
TEST(Tokenizer_expression, expr_identifier_alpha) {
  std::stringstream ss("magic");
  shaka::Tokenizer in(ss);
  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::expression(in, nullptr, interm));
}

// identifier alphanum ID
TEST(Tokenizer_expression, expr_identifier_alphanum) {
  std::stringstream ss("n0d3");
  shaka::Tokenizer in(ss);
  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::expression(in, nullptr, interm));
}

TEST(Tokenizer_expression, expr_number) {
  std::stringstream ss("3690");
  shaka::Tokenizer in(ss);
  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::expression(in, nullptr, interm));
}

using Data = shaka::Data;
using IDataTree = shaka::IDataNode<Data>;
using DataTree  = shaka::DataNode<Data>;
using Environment = shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Tokenizer_expression, expr_tree_num) {
  std::stringstream ss("808");
  shaka::Tokenizer in(ss);
  std::string interm;

  std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
  std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

  ASSERT_TRUE(shaka::parser::rule::expression(in, root, interm));

  ASSERT_EQ(shaka::Number(808), shaka::get<shaka::Number>(*root->get_child(0)->get_data()));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
