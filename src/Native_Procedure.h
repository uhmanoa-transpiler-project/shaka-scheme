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
		else if (v[0]) {
			if (v[0]->get_data()->type() == typeid(shaka::Number)){
			
			}
		}
	
	}

	virtual std::size_t get_fixed_arity() const {
		return fixed_arity;
	}

	virtual bool get_variable_arity() const {
		return variable_arity;
	}

private:
	std::size_t fixed_arity;
	bool variable_arity;
};

} // namespace shaka

#endif //NATIVE_PROCEDURE_H
