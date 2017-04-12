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

// identifier
TEST(Tokenizer_expression, expr_identifier_alpha) {
  std::stringstream ss("magic");
  shaka::Tokenizer in(ss);
  std::string interm;

  ASSERT_TRUE(shaka::parser::rule::expression(in, nullptr, interm));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
