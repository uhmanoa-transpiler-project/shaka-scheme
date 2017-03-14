#ifndef NATIVE_PROCEDURE_H
#define NATIVE_PROCEDURE_H

#include "IProcedure.h"
#include "IEnvironment.h"
#include "EvaluatorStrategies.h"
#include "Evaluator.h"
#include <functional>
#include <typeinfo>

namespace shaka {

template <typename Data, typename Key, typename Value>
class Native_Procedure : public IProcedure<Data> {
public:


	Native_Procedure(std::size_t         fixed_arity, 
					 bool                variable_arity = false) :
	fixed_arity(fixed_arity),
	variable_arity(variable_arity) {}
	
	
	}
	virtual std::vector<std::shared_ptr<IDataNode<Data>>> call(
			std::vector<std::shared_ptr<IDataNode<Data>> v) {
		if (v.size() > fixed_arity) {
			throw std::runtime_error("Wrong number of args to native procedure");
		}
		else {
			auto args_list_root = this->body_root->get_child(0);

			for (std::size_t i = 0; i < args_list_root->get_num_children(); i++) {
				auto args_symbol_ptr = args_list_root->get_child(i);


			
			
			}
		}
	
	}
	// I don't think this really evaluates a procedure call
	shaka::Evaluator<Data, Key, Value> evaluator(current_env, body_root);
	
	// What is the machine that will be used to execute the actual procedure call
	// here. This seems to do nothing. Eval_Expression does not have the ability
	// to evaluate a procedure call. Is it supposed to be Eval_Proc_Call's job?
	auto result = evaluator.evaluate(shaka::Eval_Expression<Data, Key, Value>());

	auto return_values = std::vector<std::shared_ptr<IDataNode<Data>>>();

	return_values.push_back(result);

	return return_values;

	virtual std::size_t get_fixed_arity() const {
		return fixed_arity;
	}

	virtual bool get_variable_arity() const {
		return variable_arity;
	}

private:
	std::shared_ptr<IEnvironment<Key, Data>> parent_env;
	std::shared_ptr<IEnvironment<Key, Data>> current_env;
	std::shared_ptr<IDataNode<Data>> body_root;
	std::size_t fixed_arity;
	bool variable_arity;
};

} // namespace shaka

#endif //NATIVE_PROCEDURE_H
