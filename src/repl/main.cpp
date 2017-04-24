#include <iostream> 

#include "core/parser/Tokenizer.h"
#include "core/parser/parser.h"

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
    setup_top_level.evaluate(eval::SetupTopLevel());

    // The main REPL:
    do {
        try {
            auto expr = make_node(DataNode::list());
            std::cout << "\n>>> " << std::flush;
            if (parser::parse<void>(tokenizer, expr)) {

                std::cout << "> Parsed." << std::endl;
                std::cout << *expr->car() << std::endl;

                std::cout << "> Evaluating..." << std::endl;
                Evaluator eval(expr->car(), global_env);
                auto result = eval.evaluate(eval::Expression());
                std::cout << "> Done." << std::endl;

                if (result) { std::cout << *result << std::endl; }
                else {        std::cout << std::endl;           }
            }
            else {
                std::cout << "Input rejected by parser." << std::endl;
            }
        } catch (std::runtime_error e) {
            std::cout << "Error: " << e.what() << std::endl;
            // Catch the error, flush input, and continue.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (true);

    //////////////////////////////////////////////////
    // PARSE/READ
    //////////////////////////////////////////////////
    // EVAL
    //////////////////////////////////////////////////
    // PRINT
    //////////////////////////////////////////////////
}
