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

TEST(Parser_proc_call, tokenizer_test) {
    std::stringstream ss("(+ 1 2)");
    shaka::Tokenizer tk(ss);

    shaka::Token tok1 = tk.get();
    shaka::Token tok2(shaka::Token::Type::PAREN_START, "(");

    ASSERT_EQ(tok1, tok2);
}

TEST(Parser_proc_call, proc_call_return_true) {

    std::stringstream ss("(+ 1 2)");
    shaka::Tokenizer in(ss);
    std::string interm;

    ASSERT_TRUE( shaka::parser::rule::proc_call(in, nullptr, interm) );
    std::cout << "interm: " << interm << std::endl;
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
