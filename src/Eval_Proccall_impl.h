
#ifndef SHAKA_EVAL_PROCCALL_IMPL_H
#define SHAKA_EVAL_PROCCALL_IMPL_H

#include "IEvaluatorStrategy.h"
#include "IDataNode.h"
#include "IEnvironment.h"
#include "IProcedure.h"
#include "Data.h"

#include "Procedure.h"

#include <vector>
#include <memory>
#include <type_traits>

#include "DataNode.h"
#include "Eval_Expression.h"
#include "Eval_Proccall.h"

#include "Eval_PrintTree.h"

#include "Eval_Expression_impl.h"

#include "Procedure_impl.h"
// attempts to get the procedure bound in the current environment
// and call it on the arguments condained as the child nodes of the
// list node that the procedure is called on
// returns a pointer to the list node with its child node(s)
// updated to be the result(s) of the procedure call

namespace shaka {
namespace eval {

    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;

	std::shared_ptr<shaka::IDataNode<T>> Proc_Call::evaluate(std::shared_ptr<shaka::IDataNode<T>> node,
			std::shared_ptr<shaka::IEnvironment<Key, Value>> env) {
		
		// instantiate an evaluator on the child node which should either hold a lambda or
		// a symbol that refers to a procedure in the environment or its parent env
		shaka::Evaluator evaluator(node->get_child(0), env);

        std::cout << "@Proccall" << std::endl;
        shaka::Evaluator evaluator2(node, env);
        evaluator2.evaluate(shaka::eval::PrintTree<std::cout>());

		// get the procedure associated with the symbol or lambda 
		// in the first child of the PROC_CALL node in the environment
        std::cout << "@Proccall : Procedure?" << std::endl;
		Value proc = evaluator.evaluate(shaka::eval::Expression()); 
	
		//did we successfully get a defined procedure?
		if (proc->get_data()->type() == typeid(shaka::Procedure)) {
			std::vector<Value> args;
			std::shared_ptr<shaka::IDataNode<T>> list_node = node->get_child(1);
			std::shared_ptr<shaka::IDataNode<T>> next_argument;
			
			// if so, get all of the data out of the child nodes of the
			// LIST node, evaluate the arguments that we get 
			// and place them in an argument vector to pass to proc
			for (size_t i = 0; i < list_node->get_num_children(); i++) {
                std::cout << "@Proccall : Args : " << i << std::endl;
				next_argument = list_node->get_child(i);
				shaka::Evaluator arg_evaluator(next_argument, env);
				args.push_back(arg_evaluator.evaluate(shaka::eval::Expression()));
			}
			
			// call the proc on the args vector and save the result in a
			// new vector of results
            std::cout << "@Proccall : Call" << std::endl;
			std::vector<Value> result = shaka::get<shaka::Procedure>(*proc->get_data()).call(args);

            auto results_node = std::make_shared<shaka::DataNode<shaka::Data>>(shaka::MetaTag::LIST);
			// add new children to the LIST node, which are the results
			// of our procedure call
			for (std::size_t i = 0; i < result.size(); i++) {
                std::cout << "@Proccall : Building Result Tree List(" << i << ")" << std::endl;
				results_node->push_child(*result[i]->get_data());
			}
			
            std::cout << "@Proccall : Returning tree list" << std::endl;
			return results_node;
		}
	
		// if we didn't manage to get a defined procedure out of the environment
		else {
			return node;
		}
	}

} // namespace eval
} // namespace shaka
#endif // SHAKA_EVAL_PROCCALL_IMPL_H
