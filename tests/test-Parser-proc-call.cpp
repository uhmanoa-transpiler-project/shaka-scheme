#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <vector>


#include "parser/Token.h"
#include "parser/Tokenizer.h"

#include "parser/rule_proc_call.h"
#include "parser/rule_proc_call_impl.h"


TEST(Parser_proc_call, token_constructor) {
    shaka::Token(
            shaka::Token::Type::INVALID,
            "(+ 1 2)"
            );
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
