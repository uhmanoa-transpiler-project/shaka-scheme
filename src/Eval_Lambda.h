
#ifndef SHAKA_EVAL_LAMBDA_H
#define SHAKA_EVAL_LAMBDA_H

#include <type_traits>
#include <stdexcept>
#include <map>
#include "IEvaluatorStrategy.h"
#include "IProcedure.h"

#include"Procedure.h"
#include "Eval_Expression_impl.h"

namespace shaka {

/// Encapsulates the EvaluatorStrategy classes
namespace eval {

/// brief Evaluates the Lambda procedure call
/// Creates a Procedure object by calling the Procedure constructor

class Lambda : public shaka::IEvaluatorStrategy {

    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
    std::shared_ptr<IDataNode<T>> evaluate(
        std::shared_ptr<IDataNode<T>> node,
        std::shared_ptr<IEnvironment<Key, Value>> env
    ) {
        /// brief Sets the number of input parameters to the procedure
        /// The 'node' has two children. The first child is the list of 
        /// input parameters. The second child is the body of the procedure. 
        /// fixed_arity holds the number of input parameters that are not a list
        /// var_arity is true if one of the input parameters is a list
        std::size_t fixed_arity;
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

                    if(shaka::get<shaka::MetaTag>(*params->get_child(i)->get_data())
                         == shaka::MetaTag::LIST ){
                        if(i == num_param-1){
                            var_arity = true;
                            
                        }
                        else {
                            throw std::runtime_error("Lambda: list must be last argument");
                        }
                    }
                }
                else{
                    throw std::runtime_error("Lamba: argument member is not a symbol");
                }
            }
            if(var_arity == true){
                fixed_arity = num_param -1;
            }
            else {
                fixed_arity = 0;
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
};

} // namespace eval

} // namespace shaka

#endif // SHAKA_EVAL_LAMBDA_H