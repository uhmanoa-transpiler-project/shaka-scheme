#ifndef SHAKA_STDPROC_NUMBERS_ARITHMETIC_IMPL_H
#define SHAKA_STDPROC_NUMBERS_ARITHMETIC_IMPL_H

#include "Number.h"
#include "IDataNode.h"
#include "DataNode.h"
#include "Data.h"
#include <functional>
#include <typeinfo>
#include <vector>
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
	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>();
	result_value->set_data(result);
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
	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>();
	result_value->set_data(result);
	result_vector.push_back(result_value);

	return result_vector;
}

Function mul_numbers_f = mul_numbers;

// (- z)
Args neg_numbers(Args args) {
	shaka::Number result = shaka::Number(0);

	result = result - shaka::get<shaka::Number>(*args[0]->get_data());

	Args result_vector;
	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>();
	result_value->set_data(result);
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
	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>();
	result_value->set_data(result);
	result_vector.push_back(result_value);

	return result_vector;

}

Function sub_numbers_f = sub_numbers;

// (/ z1)
Args reciprocal_numbers(Args args) {
	shaka::Number result = shaka::Number(1);
	result = result / shaka::get<shaka::Number>(*args[0]->get_data());
	Args result_vector;
	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>();
	result_value->set_data(result);
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

	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>();
	result_value->set_data(result);
	Args result_vector = {result_value};

	return result_vector;

}

Function div_numbers_f = div_numbers;

// (abs x)
// (floor/ n1 n2)
// (floor-quotient n1 n2)
// (floor-remainder n1 n2)
// (truncate/ n1 n2)
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

#endif // SHAKA_STDPROC_NUMBERS_ARITHMETIC_IMPL_H
