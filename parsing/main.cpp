#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <deque>

#include <boost/variant.hpp>

#include "Token.h"
#include "Tokenizer.h"


int main() {

    std::stringstream ss("( \"asdf\" ) ; asdfasdfasdf\n)");
    shaka::Tokenizer tokenizer(ss);

    using Type = shaka::Token::Type;
    std::vector<shaka::Token> expected {
        shaka::Token(Type::PAREN_START, "("),
        shaka::Token(Type::STRING, "asdf"),
        shaka::Token(Type::PAREN_END, ")"),
        shaka::Token(Type::PAREN_END, ")")
    };

    std::vector<shaka::Token> input;
    do {
        shaka::Token t = tokenizer.get();
        if (t != Type::END_OF_FILE) {
            input.push_back(t);
        } else {
            break;
        }
    } while (true);
   
    for (unsigned i = 0; i < input.size(); ++i) {
        auto token = input[i];
        auto token2 = expected[i];

        if (token == token2) {
            std::cout << "correct" << std::endl;
        } else {
            std::cout << "incorrect" << std::endl;
        }
    }







    std::stringstream ss1("(\t quantifier + / asdf \"qwer\"\n)");

    expected.clear(); 
    expected = {
        shaka::Token(Type::PAREN_START, "("),
        shaka::Token(Type::IDENTIFIER, "quantifier"),
        shaka::Token(Type::IDENTIFIER, "+"),
        shaka::Token(Type::IDENTIFIER, "/"),
        shaka::Token(Type::IDENTIFIER, "asdf"),
        shaka::Token(Type::STRING, "qwer"),
        shaka::Token(Type::PAREN_END, ")")
    };

    input.clear();
    shaka::Tokenizer tokenizer1(ss1);
    do {
        shaka::Token t = tokenizer1.get();
        if (t != Type::END_OF_FILE) {
            input.push_back(t);
        } else {
            break;
        }
    } while (true);
   
    for (unsigned i = 0; i < input.size(); ++i) {
        auto token = input[i];
        auto token2 = expected[i];

        if (token == token2) {
            std::cout << "correct" << std::endl;
        } else {
            std::cout << "incorrect" << std::endl;
        }
    }



    std::stringstream ss2("|asdf\t\n$$|");

    expected.clear(); 
    expected = {
        shaka::Token(Type::IDENTIFIER, "asdf\t\n$$"),
    };

    input.clear();
    shaka::Tokenizer tokenizer2(ss2);
    do {
        shaka::Token t = tokenizer2.get();
        if (t != shaka::Token(Type::END_OF_FILE)) {
            input.push_back(t);
        } else {
            break;
        }
    } while (true);
   
    for (unsigned i = 0; i < input.size(); ++i) {
        auto token = input[i];
        auto token2 = expected[i];

        if (token == token2) {
            std::cout << "correct" << std::endl;
        } else {
            std::cout << "incorrect" << std::endl;
        }
    }


    std::stringstream ss3("#\\newline #\\t");

    expected.clear(); 
    expected = {
        shaka::Token(Type::CHARACTER, "\n"),
        shaka::Token(Type::CHARACTER, "t"),
    };

    input.clear();
    shaka::Tokenizer tokenizer3(ss3);
    do {
        shaka::Token t = tokenizer3.get();
        if (t != shaka::Token(Type::END_OF_FILE)) {
            input.push_back(t);
        } else {
            break;
        }
    } while (true);
   
    for (unsigned i = 0; i < input.size(); ++i) {
        auto token = input[i];
        auto token2 = expected[i];

        if (token == token2) {
            std::cout << "correct 3" << std::endl;
        } else {
            std::cout << "incorrect 3" << std::endl;
        }
    }

    return 0;
}

