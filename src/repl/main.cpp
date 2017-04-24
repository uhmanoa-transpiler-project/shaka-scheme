#include <iostream> 

#include "core/parser/Tokenizer.h"

#include "core/base/Core.h"
#include "core/eval/Eval.h"


int main() {
    // A few type alias for convenience.
    using namespace shaka;

    // Create the tokenizer.
    Tokenizer tokenizer(std::cin);     

    // Create the global environment.
    EnvPtr global_env = std::make_shared<Environment>(nullptr);

    // Setup the top-level bindings
    Evaluator setup_top_level(nullptr, global_env);

    Token t(shaka::Token::Type::END_OF_FILE);
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

    //////////////////////////////////////////////////
    // PARSE/READ
    //////////////////////////////////////////////////
    // EVAL
    //////////////////////////////////////////////////
    // PRINT
    //////////////////////////////////////////////////
}
