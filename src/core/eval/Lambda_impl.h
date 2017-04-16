#ifndef SHAKA_CORE_EVAL_LAMBDA_IMPL_H
#define SHAKA_CORE_EVAL_LAMBDA_IMPL_H

#include "core/base/Procedure.h"
#include "core/eval/Lambda.h"

namespace shaka {
namespace eval {

NodePtr Lambda::evaluate(NodePtr node, EnvPtr env) {
   

    std::size_t fixed_arity =0;
    bool var_arity = false; 
    shaka::ListPtr params = node->car();
    std::size_t num_params = params->length();

    while(!params->is_null()){ 
        if(params->is_symbol()){
            //get symbol, find in vector
            //if not in vector, add to vector, increment arity
            fixed_arity++;
            //else throw duplicate symbol
        }
        else if(params->is_list()){
            //check that it is the last one in the list 
            //else throw list must be last
            var_arity = true;
        }
        else {
            //throw not symbol not list

        }
        params = params->cdr();
        
        
    }
    
    NodePtr proc = std::make_shared<shaka::DataNode> (shaka::Procedure (
        env,       
        node,    
        fixed_arity,
        var_arity
    ));
    return proc;
}

} // namespace eval
} // namespace shaka


#endif // SHAKA_CORE_EVAL_LAMBDA_IMPL_H