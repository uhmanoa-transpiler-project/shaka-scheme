#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <deque>

#include <boost/variant.hpp>

#include "Token.h"
#include "Tokenizer.h"


int main() {
    shaka::Tokenizer tokenizer(std::cin);

    shaka::Token t(shaka::Token::Type::END_OF_FILE);
    do {
        try {
            std::cout << "\n>>> " << std::flush;
            t = tokenizer.get();
        } catch (...) {
            // Catch the error, flush input, and continue.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // Mark the current token as invalid before continuing.
            t = shaka::Token(shaka::Token::Type::INVALID);
        }
        std::cout << t << std::endl;
    } while (t != shaka::Token(shaka::Token::Type::END_OF_FILE));

    return 0;
}