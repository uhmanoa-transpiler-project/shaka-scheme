
#ifndef SHAKA_PROCCALL_IMPL_H
#define SHAKA_PROCCALL_IMPL_H

#include "core/eval/Proccall.h"
#include "core/base/Core.h"
#include "core/base/Evaluator.h"


// attempts to get the procedure bound in the current environment
// and call it on the arguments condained as the child nodes of the
// list node that the procedure is called on
// returns a pointer to the list node with its child node(s)
// updated to be the result(s) of the procedure call

namespace shaka {
namespace eval {

	NodePtr ProcCall::evaluate(NodePtr list, EnvPtr env) {
		// Make sure that we are working with a proper list
        //std::cout << "@ProcCall" << std::endl;
        //std::cout << *list << std::endl;
		if (!list->is_list()) {
			throw std::runtime_error("eval.ProcCall: argument is not a list");
			return nullptr;
		}
		
        // instantiate an evaluator on the car of the list which should either hold a lambda or
        // a symbol that refers to a procedure in the environment or its parent env
        shaka::Evaluator evaluator(list->car(), env);


        // get the procedure associated with the symbol or lambda 
        // in the first first element of the list
        NodePtr proc = evaluator.evaluate(shaka::eval::Expression()); 
    
        //did we successfully get a defined procedure?
        if (proc->is_procedure()) {
            //std::cout << "@ProcCall: Identifier operand procedure." << std::endl;
            std::vector<NodePtr> args;
            NodePtr next_argument;
            NodePtr args_list = list->cdr();
            //std::cout << "@ProcCall: Got args_list as list->cdr()." << std::endl;
            //std::cout << *args_list << std::endl;
            
            // if so, get all of the data out of the arguments list
            // evaluate the arguments that we get 
            // and place them in an argument vector to pass to proc
            int arg_no = 0;
            if (proc->is_scheme_procedure() ||
                proc->is_native_procedure()) {
                while (!args_list->is_null()) {
                    //std::cout << "arg_no:" << arg_no << ": " << *args_list->car() << std::endl;
                    next_argument = args_list->car();
                    shaka::Evaluator arg_evaluator(next_argument, env);
                    next_argument = arg_evaluator.evaluate(shaka::eval::Expression());
                    args.push_back(next_argument);
                    args_list = args_list->cdr();
                    ++arg_no;
                }
            }
            else {
                while (!args_list->is_null()) {
                    //std::cout << "arg_no:" << arg_no << ": " << *args_list->car() << std::endl;
                    args.push_back(args_list->car());
                    args_list = args_list->cdr();
                    ++arg_no;
                }
            }
            
            // call the proc on the args vector and save the result in a
            // new vector of results
            if (proc->is_scheme_procedure()) {
                //std::cout << "@ProcCall: Procedure call" << std::endl;
                std::vector<NodePtr> result = get<Procedure>(proc->get_data()).call(args, env);
                
                NodePtr result_list = result[0];
                // add new children to the LIST node, which are the results
                // of our procedure call
                
                return result_list;
            }
            else if (proc->is_native_procedure()) {
                //std::cout << "@ProcCall: NativeProcedure call" << std::endl;
                std::vector<NodePtr> result = get<NativeProcedure>(proc->get_data()).call(args, env);
                
                NodePtr result_list = result[0];
                // add new children to the LIST node, which are the results
                // of our procedure call
                
                return result_list;

            }
            else if (proc->is_primitive_procedure()) {
                //std::cout << "@ProcCall: PrimitiveProcedure call" << std::endl;
                std::vector<NodePtr> result = get<PrimitiveProcedure>(proc->get_data()).call(args, env);
                //std::cout << "@ProcCall: Finshed PrimitveProcedure call" << std::endl;
               
                /// @note We do not support multiple values yet.
                ///       This involves taking the vector of items
                ///       that the procedure returns and then creating
                ///       some sort of representation of a multiple-value value
                NodePtr result_list = result[0];
                // add new children to the LIST node, which are the results
                // of our procedure call
                //for (std::size_t i = result.size(); i < 0+2; i--) {
                //    *result_list = DataNode::cons(*result[i], *result_list);
                //}
                //std::cout << *result_list << std::endl;

                return result_list;

            }
            else {
                throw std::runtime_error("eval.Proccall: Invalid procedure type");
                return list;
            }
        }
    
        // if we didn't manage to get a defined procedure out of the environment
        else {
            return list;
        }
        
        /*    
		}
        else {
            throw std::runtime_error("Eval.Proccall: Unsupported form (non-symbol as first argument in list");
            return nullptr;
        }
        */
		
	}

} // namespace eval
} // namespace shaka
#endif // SHAKA__PROCCALL_IMPL_H
