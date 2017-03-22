#include <iostream> 
#include "Evaluator.h"
#include "Procedure.h"
#include "Eval_Expression_impl.h"

#include "parser/Tokenizer.h"

#include "Environment.h"
#include "Symbol.h"


int main() {
    // A few type alias for convenience.
    using NodePtr = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    using Environment = shaka::Environment<shaka::Symbol, NodePtr>;

    // Create the tokenizer.
    shaka::Tokenizer tokenizer(std::cin);     

    // Create the global environment.
    Environment global_env(nullptr);

    /// @todo Bind the regular bindings for functions
    ///       to the environment.
    
    //////////////////////////////////////////////////
    // PARSE/READ
    //////////////////////////////////////////////////
    // EVAL
    //////////////////////////////////////////////////
    // PRINT
    //////////////////////////////////////////////////
}
