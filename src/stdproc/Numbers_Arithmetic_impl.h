#ifndef SHAKA_STDPROC_NUMBERS_ARITHMETIC_IMPL_H
#define SHAKA_STDPROC_NUMBERS_ARITHMETIC_IMPL_H

#include "Number.h"
#include "IDataNode.h"
#include "DataNode.h"
#include "Data.h"

#include "Procedure_impl.h"

#include <functional>
#include <typeinfo>
#include <vector>

namespace shaka {
namespace stdproc {

using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
//using Value = std::shared_ptr<IDataNode<Data>>;
using Args = std::vector<Value>;
using Function = std::function<Args(Args)>;

// (+ z1 ...)
Args add_numbers(Args args) {
	shaka::Number result = shaka::Number(0);
	for (std::size_t i = 0; i < args.size(); i++) {
		result = result + shaka::get<shaka::Number>(*args[i]->get_data());
	}

	Args result_vector;
	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);
	result_vector.push_back(result_value);

	return result_vector;
}

Function add_numbers_f = add_numbers;

// (* z1 ...)
Args mul_numbers(Args args) {
	shaka::Number result = shaka::Number(1);
	for (std::size_t i = 0; i < args.size(); i++) {
		result = result * shaka::get<shaka::Number>(*args[i]->get_data());
	}

	Args result_vector;
	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);
	result_vector.push_back(result_value);

	return result_vector;
}

Function mul_numbers_f = mul_numbers;

// (- z)
Args neg_numbers(Args args) {
	shaka::Number result = shaka::Number(0);

	result = result - shaka::get<shaka::Number>(*args[0]->get_data());

	Args result_vector;
	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);
	result_vector.push_back(result_value);

	return result_vector;

}

Function neg_numbers_f = neg_numbers;

// (- z1 z2 ...)
Args sub_numbers(Args args) {
	shaka::Number result = shaka::get<shaka::Number>(*args[0]->get_data());

	for (std::size_t i = 1; i < args.size(); i++) {
		result = result - shaka::get<shaka::Number>(*args[i]->get_data());
	}

	Args result_vector;
	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);
	result_vector.push_back(result_value);

	return result_vector;

}

Function sub_numbers_f = sub_numbers;

// (/ z1)
Args reciprocal_numbers(Args args) {
	shaka::Number result = shaka::Number(1);
	result = result / shaka::get<shaka::Number>(*args[0]->get_data());
	Args result_vector;
	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);
	result_vector.push_back(result_value);

	return result_vector;

}

Function reciprocal_numbers_f = reciprocal_numbers;

// (/ z1 z2 ...)
Args div_numbers(Args args) {
	shaka::Number result = shaka::get<shaka::Number>(*args[0]->get_data());

	for (std::size_t i = 1; i < args.size(); i++) {
		result = result / shaka::get<shaka::Number>(*args[i]->get_data());
	}

	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);
	Args result_vector = {result_value};

	return result_vector;

}

Function div_numbers_f = div_numbers;

// (abs x)
Args abs_numbers(Args args) {

	shaka::Number result = shaka::Number(0);
	
	shaka::Number input = shaka::get<shaka::Number>(*args[0]->get_data());

	if (input < 0) {

		result = result - shaka::get<shaka::Number>(*args[0]->get_data());
	}

	else {
		result = input;
	}

	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>();
	result_value->set_data(result);

	Args result_vector = {result_value};

	return result_vector;

}

Function abs_numbers_f = abs_numbers;

// (floor/ n1 n2)
Args floor_div_numbers(Args args) {

	shaka::Number n1 = shaka::get<shaka::Number>(*args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(*args[1]->get_data());
	shaka::Number r;
	shaka::Number q;

	if (n1 > shaka::Number(0) && n2 > shaka::Number(0)) {

		r = n1 % n2;
		q = (n1 - r) / n2;
	}

	else if (n1 < shaka::Number(0) && n2 < shaka::Number(0)) {
		r = n1 % n2;
		q = (n1 - r) / n2;
	
	}
	else {
		r = n1 % n2 * shaka::Number(-1);
		q = (n1 - r) / n2;
	}

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	
	v1->set_data(q);
	v2->set_data(r);

	Args result_vector = {v1, v2};

	return result_vector;

}

Function floor_div_numbers_f = floor_div_numbers;

// (floor-quotient n1 n2)
Args floor_quotient_numbers(Args args) {
		

	shaka::Number n1 = shaka::get<shaka::Number>(*args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(*args[1]->get_data());
	shaka::Number r;
	shaka::Number q;

	if (n1 > shaka::Number(0) && n2 > shaka::Number(0)) {

		r = n1 % n2;
		q = (n1 - r) / n2;
	}

	else if (n1 < shaka::Number(0) && n2 < shaka::Number(0)) {
		r = n1 % n2;
		q = (n1 - r) / n2;
	
	}
	else {
		r = n1 % n2 * shaka::Number(-1);
		q = (n1 - r) / n2;
	}

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	
	v1->set_data(q);

	Args result_vector = {v1};

	return result_vector;

}

Function floor_quotient_numbers_f = floor_quotient_numbers;

// (floor-remainder n1 n2)
Args floor_remainder_numbers(Args args) {
	shaka::Number n1 = shaka::get<shaka::Number>(*args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(*args[1]->get_data());
	shaka::Number r;

	if (n1 > shaka::Number(0) && n2 > shaka::Number(0)) {

		r = n1 % n2;
	}

	else if (n1 < shaka::Number(0) && n2 < shaka::Number(0)) {
		r = n1 % n2;
	
	}
	else {
		r = n1 % n2 * shaka::Number(-1);
	}

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	
	v1->set_data(r);

	Args result_vector = {v1};

	return result_vector;

}

Function floor_remainder_numbers_f = floor_remainder_numbers;

// (truncate/ n1 n2)
Args truncate_div_numbers(Args args) {
	shaka::Number n1 = shaka::get<shaka::Number>(*args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(*args[1]->get_data());

	shaka::Number r;
	shaka::Number q;


	r = n1 % n2;
	q = (n1 - r) / n2;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>();
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>();
	
	v1->set_data(q);
	v2->set_data(r);

	Args result_vector = {v1, v2};

	return result_vector;


}

Function truncate_div_numbers_f = truncate_div_numbers;
// (truncate-quotient n1 n2)
// (truncate-remainder n1 n2)

// (quotient n1 n2)
// (remainder n1 n2)
// (modulo n1 n2)

// (gcd n1 ...)
// (lcm n1 ...)

// (numerator q)
// (denominator q)

// (floor x)
// (ceiling x)
// (truncate x)
// (round x)

// (rationalize x y)

// (exp z)
// (log z)
// (log z1 z2)
// (sin z)
// (cos z)
// (tan z)
// (asin z)
// (acos z)
// (atan z)
// (atan y x)

// (square z)
// (sqrt z)

// (exact-integer-sqrt k)
// (expt z1 z2)

// DON'T DO THE COMPLEX LIBRARY PROCEDURES

// (inexact z)
// (exact z)

} // namespace stdproc
} // namespace shaka

#endif // SHAKA_STDPROC_NUMBERS_ARITHMETIC_IMPL_H
