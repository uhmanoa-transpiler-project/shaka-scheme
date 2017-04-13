#include "gtest/gtest.h"
#include "Data.h"
#include "DataNode.h"
#include "IDataNode.h"
#include "Environment.h"
#include "Evaluator.h"

#include "parser/Tokenizer.h"
#include "parser/Token.h"
#include "parser/rule_proccall.h"
#include "parser/rule_proccall_impl.h"

#include <iostream>
#include <sstream>
#include <string>

TEST(Tokenizer_proccall, proc_01) {
  std::stringstream ss("(add 1 2)");
  shaka::Tokenizer in(ss);
  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::proc_call(in, nullptr, interm));
}

using Data = shaka::Data;
using IDataTree = shaka::IDataNode<Data>;
using DataTree  = shaka::DataNode<Data>;
using Environment = shaka::Environment<shaka::Symbol, std::shared_ptr<IDataTree>>;

TEST(Tokenizer_proccall, proc_01_tree) {
  std::stringstream ss("(add 1 2)");
  shaka::Tokenizer in(ss);
  std::string interm;

  std::shared_ptr<DataTree> root = std::make_shared<DataTree>(shaka::MetaTag::LIST);
  std::shared_ptr<Environment> env = std::make_shared<Environment>(nullptr);

  ASSERT_TRUE(shaka::parser::rule::proc_call(in, root, interm));

  ASSERT_EQ(root->get_num_children(), 1);

  ASSERT_EQ(root->get_child(0)->get_num_children(), 2);

  ASSERT_EQ(root->get_child(0)->get_child(0)->get_num_children(), 0);

  ASSERT_EQ(root->get_child(0)->get_child(1)->get_num_children(), 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
