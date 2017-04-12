#ifndef SHAKA_EVAL_LAMBDA_IMPL_H
#define SHAKA_EVAL_LAMBDA_IMPL_H

#include <type_traits>

#include "IEvaluatorStrategy.h"
#include "IEnvironment.h"

#include "Symbol.h"
#include "DataNode.h"

#include "Evaluator.h"

#include "EvaluatorStrategyDefinitions.h"

#include "Eval_Lambda.h"
#include "Eval_Expression.h"

#include "Eval_Expression_impl.h"

namespace shaka {

/// Encapsulates the EvaluatorStrategy classes
namespace eval {


std::shared_ptr<IDataNode<T>> Lambda::evaluate(
    std::shared_ptr<IDataNode<T>> node,
    std::shared_ptr<IEnvironment<Key, Value>> env
) {
    using T = shaka::Data;
    /// brief Sets the number of input parameters to the procedure
    /// The 'node' has two children. The first child is the list of 
    /// input parameters. The second child is the body of the procedure. 
    /// fixed_arity holds the number of input parameters that are not a list
    /// var_arity is true if one of the input parameters is a list
    std::size_t fixed_arity =0;
    bool var_arity = false; 
    std::shared_ptr<IDataNode<T>> params = node->get_child(0);
    int num_param = params->get_num_children();
    std::map<shaka::Symbol, bool> symbols;

    if(num_param < 1){
        fixed_arity = 0;    
        var_arity = false;
    }
    else {
        for(int i = 0; i < num_param; i++){
            if(auto *ptr = shaka::get<shaka::Symbol>(params->get_child(i)->get_data().get())){
                if(symbols.find(*ptr)!= symbols.end()){
                    throw std::runtime_error("Lambda: arguments must be different");
                }
                else{
                    symbols[*ptr]=true;
                }
            }

              else if(shaka::get<shaka::MetaTag>(*params->get_child(i)->get_data())
                     == shaka::MetaTag::LIST ){
                    if(i == num_param-1){
                        var_arity = true;
                        
                    }
                    else {
                        throw std::runtime_error("Lambda: list must be last argument");
                    }
                }
            
            else{
                throw std::runtime_error("Lambda: argument member is not a symbol");
            }
        }
        if(var_arity == true){
            fixed_arity = num_param -1;
        }
        else {
            fixed_arity = num_param;
        }


    }
    // constructor for Procedure
    auto sptr = std::make_shared<DataNode<T>>( shaka::Procedure (
        env,       
        node,    
        fixed_arity,
        var_arity
    ));

    return sptr;
}

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_LAMBDA_H
