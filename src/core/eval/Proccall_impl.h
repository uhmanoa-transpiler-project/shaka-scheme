
#ifndef SHAKA_PROCCALL_IMPL_H
#define SHAKA_PROCCALL_IMPL_H

#include "core/eval/Proccall.h"
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
		if (!list->is_list()) {
			throw std::runtime_error("eval.ProcCall: argument is not a list");
			return nullptr;
		}
		
		// Make sure that the first item in the list is a Symbol
		if (list->car()->is_symbol()) {
		
			// instantiate an evaluator on the car of the list which should either hold a lambda or
			// a symbol that refers to a procedure in the environment or its parent env
			shaka::Evaluator evaluator(list->car(), env);


			// get the procedure associated with the symbol or lambda 
			// in the first first element of the list
			NodePtr proc = evaluator.evaluate(shaka::eval::Expression()); 
		
			//did we successfully get a defined procedure?
			if (proc->car()->get_data().type() == typeid(shaka::Procedure)) {
				std::vector<NodePtr> args;
				NodePtr next_argument;
				NodePtr args_list = list->cdr();
				
				// if so, get all of the data out of the arguments list
				// evaluate the arguments that we get 
				// and place them in an argument vector to pass to proc
				while(!args_list->is_null()) {
					next_argument = args_list->car();
					shaka::Evaluator arg_evaluator(next_argument, env);
					next_argument = arg_evaluator.evaluate(shaka::eval::Expression());
					args.push_back(next_argument);
					args_list = args_list->cdr();
				}
				
				// call the proc on the args vector and save the result in a
				// new vector of results
				std::vector<NodePtr> result = get<Procedure>(proc->get_data()).call(args, env);
				
				NodePtr result_list = std::make_shared<DataNode>(result[result.size() - 1]);
				// add new children to the LIST node, which are the results
				// of our procedure call
				for (std::size_t i = result.size() - 2; i > 0; i--) {
					*result_list = DataNode::cons(result[i], result_list);
					
				}
				
				return result_list;
			}
		
			// if we didn't manage to get a defined procedure out of the environment
			else {
				return list;
			}
			
		
		}
		
	}

} // namespace eval
} // namespace shaka
#endif // SHAKA__PROCCALL_IMPL_H
