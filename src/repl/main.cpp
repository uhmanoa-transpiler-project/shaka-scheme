#include <iostream> 
#include <fstream>

#include "core/parser/Tokenizer.h"
#include "core/parser/parser.h"

#include "core/base/Core.h"
#include "core/eval/Eval.h"


int main(int argc, char** argv) {
    
    std::ifstream input_file;
    if (argc == 2) {
        input_file.open(argv[1]);
    }
    // A few type alias for convenience.
    using namespace shaka;

    std::cout << "> shaka-scheme, Version 0.0" << std::endl;

    std::shared_ptr<Tokenizer> tokenizer;
    // Create the tokenizer.
    if (argc == 2) {
        tokenizer = std::make_shared<Tokenizer>(input_file); 
    }
    else {
        tokenizer = std::make_shared<Tokenizer>(std::cin); 
    }

    // Create the global environment.
    EnvPtr global_env = std::make_shared<Environment>(nullptr);

    // Setup the top-level bindings
    Evaluator setup_top_level(nullptr, global_env);
    setup_top_level.evaluate(eval::SetupTopLevel());
    std::cout << "> Initialized top-level environment." << std::endl;
    std::cout << "> Ready for input." << std::endl;

    // The main REPL:
    do {
        try {
            auto expr = make_node(DataNode::list());
            std::cout << "\n>>> " << std::flush;
           
            bool parse_success = false;
            // Determine if we're done parsing yet
            try {
                parse_success = parser::parse<void>(*tokenizer, expr);
            }
            catch (parser::end e) {
                std::cout << "> Terminating input." << std::endl;
                return 0;
            }

            // If parsing was successful, then evaluate the next
            // expression.
            if (parse_success) {

                //std::cout << "> Parsed." << std::endl;
                //std::cout << *expr->car() << std::endl;

                //std::cout << "> Evaluating..." << std::endl;
                Evaluator eval(expr->car(), global_env);
                auto result = eval.evaluate(eval::Expression());
                //std::cout << "> Done." << std::endl;

                if (result) { std::cout << *result << std::endl; }
                else {        std::cout << std::endl;           }
            }
            else {
                std::cout << "Error: Input rejected by parser." << std::endl;
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
