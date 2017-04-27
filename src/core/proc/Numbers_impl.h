#ifndef SHAKA_STDPROC_NUMBERS_IMPL_H
#define SHAKA_STDPROC_NUMBERS_IMPL_H

#include "core/base/Number.h"
#include "core/base/DataNode.h"
#include "core/base/Data.h"

#include "core/base/Environment.h"
#include <functional>
#include <typeinfo>
#include <vector>

namespace shaka {
namespace stdproc {

using Args = std::vector<NodePtr>;
using Function = std::function<Args(Args, EnvPtr)>;
namespace impl {
// (number? obj)
// (complex? obj)
// (real? obj)
// (rational? obj)
// (integer? obj)

// (exact? z)
// (inexact? z)

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
Function equals = impl::num_equals;
Function less_than_or_eq = impl::num_less_than_or_eq;
Function greater_than_or_eq = impl::num_greater_than_or_eq;
Function less_than = impl::num_less_than;
Function greater_than = impl::num_greater_than;
} // namespace stdproc
} // namespace shaka

#endif // SHAKA_STDPROC_NUMBERS_IMPL_H
