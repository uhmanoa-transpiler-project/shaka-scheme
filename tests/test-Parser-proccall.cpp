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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
