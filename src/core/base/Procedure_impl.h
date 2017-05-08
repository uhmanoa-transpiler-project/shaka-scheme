#ifndef SHAKA_CORE_PROCEDURE_IMPL_H
#define SHAKA_CORE_PROCEDURE_IMPL_H

#include "core/base/Evaluator.h"
#include "core/base/Procedure.h"
#include "core/eval/ProcedureBody.h"

//#include "core/eval/ProcedureBody_impl.h"

namespace shaka {

void
Procedure::print_body(std::ostream& out) const {
    out << *this->body_root;
}

std::vector<std::shared_ptr<DataNode>> 
Procedure::call (std::vector<std::shared_ptr<DataNode>> v,
                 std::shared_ptr<Environment>           env) {

    // Turn off env unused warning
    static_cast<void>(env);
    // std::cout << "@Procedure.call" << std::endl;
    // Get the arguments, bind them without evaluating to the
    // names in the arguments subtree (the first child) of this
    // root node.
    auto args_list_root = this->body_root->car();
    auto curr_env       = this->curr_env;
    // std::cout << "args_list_root: " << *args_list_root << std::endl;
	// std::cout << "args_list_root->length(): " << args_list_root->length() << std::endl;
    // std::cout << "body_expressions: " << *this->body_root->cdr() << std::endl;
	
	if (args_list_root->is_symbol()) {
		//std::cout << "Procedure.call: Args list is variadic form" << std::endl;
		
		auto args_list_ptr = std::make_shared<shaka::DataNode>(shaka::DataNode::list());
		// Collect all of the arguments into a list to bind to the symbol parameter
		for (
			int i = v.size() - 1;
			i >= 0;
			i--
		) {
			args_list_ptr = std::make_shared<shaka::DataNode>(
					shaka::DataNode::cons(*v[i], *args_list_ptr));
		}
		
		// Bind the list to the symbol parameter

		curr_env->set_value(
			shaka::get<shaka::Symbol>(args_list_root->get_data()),
			args_list_ptr
		);

	}
    /// For each child, verify it's a symbol.
	else {
		std::size_t args_list_length = args_list_root->length();
		// std::cout << "args_list_length: " << args_list_length << std::endl;
		// A very subtle bug was occuring here that would undermine multi argument lambdas
		// The for loop was checking the value of i against args_list_root->length() on each
		// iteration. However because we set args_list_root to be equal to args_list_root->cdr()
		// on each iteration, we were missing the last argument every time. The fix was simple,
		// save the original args_list_length to a variable and check the value of i against
		// that length on each iteration. Quite a subtle bug indeed. -- Mortrax 
		for (
			std::size_t i = 0;
			i < args_list_length;
			i++
		) {
			// Get the child node pointer.
			auto args_symbol_ptr = args_list_root->car();
		    // std::cout << "Symbol(" << i << "): " << *args_symbol_ptr << std::endl;
			// If we have a symbol, bind it.
			if (args_symbol_ptr->is_symbol()) {
				Data symbol = args_symbol_ptr->get_data();
				NodePtr value  = v[i];
				// std::cout << "Value being bound from" << *v[i] << std::endl;
				// Set the value in our current environment
				curr_env->set_value(
					shaka::get<shaka::Symbol>(symbol),
					value);
			   // std::cout << get<Symbol>(symbol) << " : " << *make_node(value) << std::endl;
			} else {
				/// @todo Define better semantics for procedure call
				///       failure.
				// Failure
				throw std::runtime_error("Procedure: argument list member node is not a Symbol");
				return std::vector<std::shared_ptr<DataNode>>{nullptr};
			}
			//std::cout << *args_list_root << std::endl;
			if (args_list_root->is_list()) {
				args_list_root = args_list_root->cdr();
				// std::cout << *args_list_root << std::endl;
			}
			else {
				// std::cout << "Breaking" << std::endl;
				break;
			}
		}
	}
    // Setup an Evaluator on the current environment and
    // a copy of the body root node.
    //parent_env->print_bindings(std::cout);
    //curr_env->print_bindings(std::cout);
    shaka::Evaluator evaluator(this->body_root->cdr(), curr_env);

    // Evaluate the body of the procedure on the right side.
    //
    // DO NOT DESTROY THE TREE
    auto result = evaluator.evaluate(shaka::eval::ProcedureBody());

    // If the root of the result list is multiple values,
    // then you'll need to get a multiple value list.
    //
    // Tuples, maybe? Hm...
    //
    auto return_values =
        std::vector<std::shared_ptr<DataNode>>();

    // Then, return the list.
    return_values.push_back(result);
    
    return return_values;
}

std::ostream& operator<< (std::ostream& lhs, const shaka::Procedure& rhs) {
    // Turn off rhs unused warning
    static_cast<void>(rhs);
    lhs << "#<procedure>";
    return lhs;
}

bool operator== (const Procedure& lhs, const Procedure& rhs) {
    if (lhs.fixed_arity == rhs.fixed_arity) {
       if(lhs.variable_arity ==rhs.variable_arity){
           if(lhs.body_root==rhs.body_root)
            return true;
       }
    }
    return false;
}

}

#endif //SHAKA_PROCEDURE_IMPL_H
