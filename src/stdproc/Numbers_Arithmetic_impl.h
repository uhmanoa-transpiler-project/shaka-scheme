#ifndef SHAKA_STDPROC_NUMBERS_ARITHMETIC_IMPL_H
#define SHAKA_STDPROC_NUMBERS_ARITHMETIC_IMPL_H

#include "Number.h"
#include "IDataNode.h"
#include "DataNode.h"
#include "Data.h"

#include "Procedure_impl.h"
#include "Procedure.h"

#include <functional>
#include <typeinfo>
#include <vector>

namespace shaka {
namespace stdproc {

using Value = std::shared_ptr<shaka::IDataNode<shaka::Data>>;
//using Value = std::shared_ptr<IDataNode<Data>>;
using Args = std::vector<Value>;

using Function = std::function<Args(Args)>;
namespace impl {
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


// (- z)
Args neg_numbers(Args args) {
	shaka::Number result = shaka::Number(0);

	result = result - shaka::get<shaka::Number>(*args[0]->get_data());

	Args result_vector;
	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);
	result_vector.push_back(result_value);

	return result_vector;

}


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


// (/ z1)
Args reciprocal_numbers(Args args) {
	shaka::Number result = shaka::Number(1);
	result = result / shaka::get<shaka::Number>(*args[0]->get_data());
	Args result_vector;
	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);
	result_vector.push_back(result_value);

	return result_vector;

}


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

	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);


	Args result_vector = {result_value};

	return result_vector;

}


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

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(q);
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(r);
	
	Args result_vector = {v1, v2};

	return result_vector;

}


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

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(q);
	
	Args result_vector = {v1};

	return result_vector;

}


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

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(r);
	
	Args result_vector = {v1};

	return result_vector;

}


// (truncate/ n1 n2)
Args truncate_div_numbers(Args args) {
	shaka::Number n1 = shaka::get<shaka::Number>(*args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(*args[1]->get_data());

	shaka::Number r;
	shaka::Number q;


	r = n1 % n2;
	q = (n1 - r) / n2;

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(q);
	Value v2 = std::make_shared<shaka::DataNode<shaka::Data>>(r);
	
	Args result_vector = {v1, v2};

	return result_vector;


}

// (truncate-quotient n1 n2)
Args truncate_quotient_numbers(Args args) {
	shaka::Number n1 = shaka::get<shaka::Number>(*args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(*args[1]->get_data());

	shaka::Number r = n1 % n2;
	shaka::Number q = (n1 - r) / n2;

	Value v = std::make_shared<shaka::DataNode<shaka::Data>>(q);

	Args result_vector = {v};

	return result_vector;

}

// (truncate-remainder n1 n2)
Args truncate_remainder_numbers(Args args) {
	shaka::Number n1 = shaka::get<shaka::Number>(*args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(*args[1]->get_data());

	shaka::Number r = n1 % n2;

	Value v = std::make_shared<shaka::DataNode<shaka::Data>>(r);

	Args result_vector = {v};

	return result_vector;
}

// (quotient n1 n2)
Args quotient_numbers(Args args) {

	shaka::Number n1 = shaka::get<shaka::Number>(*args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(*args[1]->get_data());

	shaka::Number r = n1 % n2;
	shaka::Number q = (n1 - r) / n2;

	Value v = std::make_shared<shaka::DataNode<shaka::Data>>(q);

	Args result_vector = {v};

	return result_vector;

}

// (remainder n1 n2)
Args remainder_numbers(Args args) {
	shaka::Number n1 = shaka::get<shaka::Number>(*args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(*args[1]->get_data());

	shaka::Number r = n1 % n2;

	Value v = std::make_shared<shaka::DataNode<shaka::Data>>(r);

	Args result_vector = {v};

	return result_vector;
}

// (modulo n1 n2)
Args modulo_numbers(Args args) {
	
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

	Value v1 = std::make_shared<shaka::DataNode<shaka::Data>>(r);
	
	Args result_vector = {v1};

	return result_vector;
}

// (gcd n1 ...)
shaka::Number gcd_pair(shaka::Number n1, shaka::Number n2) {
	
	shaka::Number temp;
	while (n2 > shaka::Number(0)) {
		temp = n2;
		n2 = n1 % n2;
		n1 = temp;
	}
	return n1;
}

Args gcd_numbers(Args args) {

	shaka::Number result = shaka::get<shaka::Number>(*args[0]->get_data());
	shaka::Number next;
	for (std::size_t i = 1; i < args.size(); i++) {
		next = shaka::get<shaka::Number>(*args[i]->get_data());
		result = gcd_pair(result, next); 
	}

	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);

	Args result_vector = {result_value};

	return result_vector;

}


// (lcm n1 ...)
Args lcm_numbers(Args args) {
	
	shaka::Number result = shaka::get<shaka::Number>(*args[0]->get_data());
	shaka::Number next;
	shaka::Number gcd;
	for (std::size_t i = 1; i < args.size(); i++) {
		next = shaka::get<shaka::Number>(*args[i]->get_data());
		gcd = gcd_pair(result, next);
		result = (result*next)|gcd;
	}

	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);

	Args result_vector = {result_value};

	return result_vector;


}

// (numerator q)

Args numerator_numbers(Args args) {
	shaka::Number n1 = shaka::get<shaka::Number>(*args[0]->get_data());
	
	shaka::Number result(boost::get<shaka::Rational>(n1.get_value()).get_numerator());

	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);
	
	Args result_vector = {result_value};

	return result_vector;


}

// (denominator q)
Args denominator_numbers(Args args) {
	shaka::Number n1 = shaka::get<shaka::Number>(*args[0]->get_data());

	shaka::Number result(boost::get<shaka::Rational>(n1.get_value()).get_denominator());

	Value result_value = std::make_shared<shaka::DataNode<shaka::Data>>(result);

	Args result_vector = {result_value};

	return result_vector;
}


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

} // namespace impl

Function add = impl::add_numbers;
Function mul = impl::mul_numbers;
Function neg = impl::neg_numbers;
Function sub = impl::sub_numbers;
Function reciprocal = impl::reciprocal_numbers;
Function div = impl::div_numbers;
Function abs = impl::abs_numbers;
Function floor_div = impl::floor_div_numbers;
Function floor_quotient = impl::floor_quotient_numbers;
Function floor_remainder = impl::floor_remainder_numbers;
Function truncate_div = impl::truncate_div_numbers;
Function truncate_quotient = impl::truncate_quotient_numbers;
Function truncate_remainder = impl::truncate_remainder_numbers;
Function quotient = impl::quotient_numbers;
Function remainder = impl::remainder_numbers;
Function modulo = impl::modulo_numbers;
Function gcd = impl::gcd_numbers;
Function lcm = impl::lcm_numbers;
Function numerator = impl::numerator_numbers;
Function denominator = impl::denominator_numbers;
} // namespace stdproc
} // namespace shaka

#endif // SHAKA_STDPROC_NUMBERS_ARITHMETIC_IMPL_H
