#ifndef SHAKA_STDPROC_NUMBERS_IMPL_H
#define SHAKA_STDPROC_NUMBERS_IMPL_H


#include "core/base/Number.h"
#include "core/base/DataNode.h"
#include "core/base/Data.h"
#include "core/base/Core.h"
#include "core/base/Environment.h"
#include <functional>
#include <typeinfo>
#include <vector>

using Args = std::vector<std::shared_ptr<shaka::DataNode>>;
using EnvPtr = std::shared_ptr<shaka::Environment>;
using Function = std::function<Args(Args, EnvPtr)>;  
namespace shaka {
namespace stdproc {

// (number? obj)

namespace impl{
Args isnumber(Args a, EnvPtr e){
static_cast<void>(e);
if(a[0] -> is_number()){
	shaka::Boolean b(true);
	return {std::make_shared<shaka::DataNode>(b)};
}	
else{
	shaka::Boolean c(false);
	return {std::make_shared<shaka::DataNode>(c)};
}

}
// (complex? obj)
// (real? obj)
// (rational? obj)
// (integer? obj)

// (exact? z)
Args num_exact_p(Args args, EnvPtr env) {
	static_cast<void>(env);
	if (args[0]->get_data().type() == typeid(shaka::Number) &&
		shaka::get<shaka::Number>(args[0]->get_data()).exact_p()) {
		shaka::Boolean result(true);
		return {std::make_shared<shaka::DataNode>(result)};
	}
	else {
		shaka::Boolean result(false);
		return {std::make_shared<shaka::DataNode>(result)};
	}
}
// (inexact? z)
Args num_inexact_p(Args args, EnvPtr env) {
	static_cast<void>(env);
	if (args[0]->get_data().type() == typeid(shaka::Number) &&
		shaka::get<shaka::Number>(args[0]->get_data()).inexact_p()) {
		shaka::Boolean result(true);
		return {std::make_shared<shaka::DataNode>(result)};
	}
	else {
		shaka::Boolean result(false);
		return {std::make_shared<shaka::DataNode>(result)};
	}
}

// (exact-integer? z)
// (finite? z)
// (infinite? z)
// (nan? z)

// (= z1 z2 z3 ...)
Args num_equals(Args args, EnvPtr env) {
    static_cast<void>(env);
	if (args[0]->get_data().type() != typeid(shaka::Number)) {
		throw std::runtime_error("STDPROC: Incorrect argument type to Number comparison: =");
		return args;
	}
	
    shaka::Boolean result(true);
	for (std::size_t i = 1; i < args.size(); i++) {
        if(shaka::get<shaka::Number>(args[i-1]->get_data()) 
        != shaka::get<shaka::Number>(args[i]->get_data())){
            result.set_value(false);
        } 
	}

	Args result_vector;
	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	result_vector.push_back(result_value);

	return result_vector;
}

// (< z1 z2 z3 ...)
Args num_less_than(Args args, EnvPtr env) {
    static_cast<void>(env);
	if (args[0]->get_data().type() != typeid(shaka::Number)) {
		throw std::runtime_error("STDPROC: Incorrect argument type to Number comparison: <");
		return args;
	}
    shaka::Boolean result(true);
	for (std::size_t i = 1; i < args.size(); i++) {
        if(shaka::get<shaka::Number>(args[i-1]->get_data()) 
        >= shaka::get<shaka::Number>(args[i]->get_data())){
            result.set_value(false);
        } 
	}

	Args result_vector;
	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	result_vector.push_back(result_value);

	return result_vector;
}
// (> z1 z2 z3 ...)
Args num_greater_than(Args args, EnvPtr env) {
    static_cast<void>(env);
	if (args[0]->get_data().type() != typeid(shaka::Number)) {
		throw std::runtime_error("STDPROC: Incorrect argument type to Number comparison: >");
		return args;
	}
    shaka::Boolean result(true);
	for (std::size_t i = 1; i < args.size(); i++) {
        if(shaka::get<shaka::Number>(args[i-1]->get_data()) 
        <= shaka::get<shaka::Number>(args[i]->get_data())){
            result.set_value(false);
        } 
	}

	Args result_vector;
	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	result_vector.push_back(result_value);

	return result_vector;
}
// (<= z1 z2 z3 ...)
Args num_less_than_or_eq(Args args, EnvPtr env) {
    static_cast<void>(env);
	if (args[0]->get_data().type() != typeid(shaka::Number)) {
		throw std::runtime_error("STDPROC: Incorrect argument type to Number comparison: <=");
		return args;
	}
    shaka::Boolean result(true);
	for (std::size_t i = 1; i < args.size(); i++) {
        if(shaka::get<shaka::Number>(args[i-1]->get_data()) 
        > shaka::get<shaka::Number>(args[i]->get_data())){
            result.set_value(false);
        } 
	}

	Args result_vector;
	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	result_vector.push_back(result_value);

	return result_vector;
}
// (>= z1 z2 z3 ...)
Args num_greater_than_or_eq(Args args, EnvPtr env) {
    static_cast<void>(env);
	if (args[0]->get_data().type() != typeid(shaka::Number)) {
		throw std::runtime_error("STDPROC: Incorrect argument type to Number comparison: =>");
		return args;
	}
    shaka::Boolean result(true);
	for (std::size_t i = 1; i < args.size(); i++) {
        if(shaka::get<shaka::Number>(args[i-1]->get_data()) 
        < shaka::get<shaka::Number>(args[i]->get_data())){
            result.set_value(false);
        } 
	}

	Args result_vector;
	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	result_vector.push_back(result_value);

	return result_vector;
}
// (zero? z)
Args num_is_zero(Args args, EnvPtr env) {
	static_cast<void>(env);
	shaka::Boolean result(false);
	if (args[0]->get_data().type() == typeid(shaka::Number) &&
			shaka::get<shaka::Number>(args[0]->get_data()) == shaka::Number(0)) {
		result.set_value(true);
	}

	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	Args result_vector = {result_value};
	
	return result_vector;
	
}
// (positive? x)
// (negative? x)
// (odd? n)
// (even? n)

// (max? x1 x2 ...)
// (min? x1 x2 ...)

// (number->string z)
// (number->string z radix)

// (string->number string)
// (string->number string radix)
} //namespace impl
Function is_number = impl::isnumber;

Function equals = impl::num_equals;
Function less_than_or_eq = impl::num_less_than_or_eq;
Function greater_than_or_eq = impl::num_greater_than_or_eq;
Function less_than = impl::num_less_than;
Function greater_than = impl::num_greater_than;
Function zerop = impl::num_is_zero;
Function exactp = impl::num_exact_p;
Function inexactp = impl::num_inexact_p;
} // namespace stdproc
} // namespace shaka

#endif // SHAKA_STDPROC_NUMBERS_IMPL_H
