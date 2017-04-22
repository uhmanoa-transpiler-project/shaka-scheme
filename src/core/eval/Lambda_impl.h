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
    std::map<shaka::Symbol, bool> param_symbols;

    if (params->is_list()){
        if (params->is_null()){
            //CASE 1:  ( lambda () 1 )
            fixed_arity = 0;
            var_arity = false;
        }
        else {
            //CASE 2: (lambda ( x y z) (body))
            while(!params->is_null()){
                if(params->car()->is_symbol()){
                    //get symbol, find in map
                    shaka::Symbol s = shaka::get<shaka::Symbol>(params->car()->get_data());
                    if(param_symbols.find(s)!=param_symbols.end()){
                        throw std::runtime_error("Lambda: arguments must be unique");
                    }
                    else {
                        fixed_arity++;
                        param_symbols[s] = true;
                    }
                }
                params = params->cdr();
            }
            
        }
    }
    else if (params->is_pair()){
        // CASE 3: (lambda ( x y . z) (body))
            while(params->is_pair()){
                if(params->car()->is_symbol()){
                    //get symbol, find in map
                    shaka::Symbol s = shaka::get<shaka::Symbol>(params->car()->get_data());
                    if(param_symbols.find(s)!=param_symbols.end()){
                        throw std::runtime_error("Lambda: arguments must be unique");
                    }
                    else {
                        fixed_arity++;
                        param_symbols[s] = true;
                    }
                    params = params->cdr();
                }
                else {
                    throw std::runtime_error("Lambda: argument is not a symbol");
                }
            }
            if(params->is_symbol()){
                shaka::Symbol s = shaka::get<shaka::Symbol>(params->get_data());
                if(param_symbols.find(s)!=param_symbols.end()){
                    throw std::runtime_error("Lambda: arguments must be unique");
                }
                else {
                    var_arity = true;
                    param_symbols[s] = true;
                }
            }
            else {
                throw std::runtime_error("Lambda: argument is not a symbol");
            }


    }
    else {
        // CASE 4: ( lambda x x )
        fixed_arity = 0;
        var_arity = true;
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
