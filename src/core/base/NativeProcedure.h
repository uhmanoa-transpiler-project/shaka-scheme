#ifndef SHAKA_CORE_BASE_NATIVEPROCEDURE_H
#define SHAKA_CORE_BASE_NATIVEPROCEDURE_H

#include "core/base/IProcedure.h"
#include "core/base/Environment.h"
//#include "Evaluator.h"
#include "core/base/Data.h"
#include <functional>
#include <typeinfo>
#include <vector>
namespace shaka {

class NativeProcedure : public IProcedure {
public:
    using T = shaka::Data;
    using Key = shaka::Symbol;
    using Value = shaka::Data;
    using IEnvPtr = std::shared_ptr<shaka::Environment>;
    //using Value = std::shared_ptr<IDataNode<Data>>;
    using Args = std::vector<Value>;
    using Function = std::function<Args(Args, IEnvPtr)>;


	NativeProcedure(
        Function	   func,
        std::size_t    fixed_arity, 
        bool           variable_arity = false) :
		func(func),
		fixed_arity(fixed_arity),
		variable_arity(variable_arity) {}
	
	
	virtual Args call(Args v, IEnvPtr env) {
		if (v.size() > fixed_arity && !variable_arity) {
			throw std::runtime_error("Wrong number of args to native procedure");
		}
		
		else {

			return func(v, env);
		}
	
	}
	// I don't think this really evaluates a procedure call
	/*shaka::Evaluator<Data, Key, Value> evaluator(current_env, body_root);
	
	// What is the machine that will be used to execute the actual procedure call
	// here. This seems to do nothing. Eval_Expression does not have the ability
	// to evaluate a procedure call. Is it supposed to be Eval_Proc_Call's job?
	auto result = evaluator.evaluate(shaka::Eval_Expression<Data, Key, Value>());

	auto return_values = std::vector<std::shared_ptr<IDataNode<Data>>>();

	return_values.push_back(result);

	return return_values;*/

	virtual std::size_t get_fixed_arity() const {
		return fixed_arity;
	}

	virtual bool is_variable_arity() const {
		return variable_arity;
	}

private:
	/*std::shared_ptr<IEnvironment<Key, Data>> parent_env;
	std::shared_ptr<IEnvironment<Key, Data>> current_env;
	std::shared_ptr<IDataNode<Data>> body_root;*/
	Function func;
	std::size_t fixed_arity;
	bool variable_arity;
};

} // namespace shaka

#endif // SHAKA_CORE_BASE_NATIVEPROCEDURE_H
