#ifndef SHAKA_STDPROC_NUMBERS_ARITHMETIC_IMPL_H
#define SHAKA_STDPROC_NUMBERS_ARITHMETIC_IMPL_H

#include "core/base/Number.h"
#include "core/base/DataNode.h"
#include "core/base/Data.h"

#include "core/base/Environment.h"
#include <functional>
#include <typeinfo>
#include <vector>

namespace shaka {
namespace stdproc {

//using NodePtr = std::shared_ptr<IDataNode<Data>>;
using Args = std::vector<NodePtr>;


using Function = std::function<Args(Args, EnvPtr)>;
namespace impl {
// (+ z1 ...)
Args add_numbers(Args args, EnvPtr env) {
	if (args[0]->get_data().type() != typeid(shaka::Number)) {
		throw std::runtime_error("STDPROC: Incorrect argument type to Native Procedure: +");
		return args;
	}
	
	shaka::Number result = shaka::Number(0);
	for (std::size_t i = 0; i < args.size(); i++) {
		result = result + shaka::get<shaka::Number>(args[i]->get_data());
	}

	Args result_vector;
	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	result_vector.push_back(result_value);

	return result_vector;
}


// (* z1 ...)
Args mul_numbers(Args args, EnvPtr env) {
	if (args[0]->get_data().type() != typeid(shaka::Number)) {
		throw std::runtime_error("STDPROC: Incorrect argument type to Native Procedure: *");
	}

	shaka::Number result = shaka::Number(1);
	for (std::size_t i = 0; i < args.size(); i++) {
		result = result * shaka::get<shaka::Number>(args[i]->get_data());
	}

	Args result_vector;
	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	result_vector.push_back(result_value);

	return result_vector;
}


// (- z)
Args neg_numbers(Args args, EnvPtr env) {
	if (args[0]->get_data().type() != typeid(shaka::Number)) {
		throw std::runtime_error("STDPROC: Incorrect argument type to Native Procedure: -");
	}
	shaka::Number result = shaka::Number(0);

	result = result - shaka::get<shaka::Number>(args[0]->get_data());

	Args result_vector;
	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	result_vector.push_back(result_value);

	return result_vector;

}


// (- z1 z2 ...)
Args sub_numbers(Args args, EnvPtr env) {
	shaka::Number result = shaka::get<shaka::Number>(args[0]->get_data());

    if (args.size() == 1) {
        return neg_numbers(args, env);
    }

	for (std::size_t i = 1; i < args.size(); i++) {
		result = result - shaka::get<shaka::Number>(args[i]->get_data());
	}

	Args result_vector;
	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	result_vector.push_back(result_value);

	return result_vector;

}


// (/ z1)
Args reciprocal_numbers(Args args, EnvPtr env) {
	shaka::Number result = shaka::Number(1);
	result = result / shaka::get<shaka::Number>(args[0]->get_data());
	Args result_vector;
	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	result_vector.push_back(result_value);

	return result_vector;

}


// (/ z1 z2 ...)
Args div_numbers(Args args, EnvPtr env) {
	shaka::Number result = shaka::get<shaka::Number>(args[0]->get_data());

	for (std::size_t i = 1; i < args.size(); i++) {
		result = result / shaka::get<shaka::Number>(args[i]->get_data());
	}

	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	Args result_vector = {result_value};

	return result_vector;

}


// (abs x)
Args abs_numbers(Args args, EnvPtr env) {

	shaka::Number result = shaka::Number(0);
	
	shaka::Number input = shaka::get<shaka::Number>(args[0]->get_data());

	if (input < 0) {

		result = result - shaka::get<shaka::Number>(args[0]->get_data());
	}

	else {
		result = input;
	}

	NodePtr result_value = std::make_shared<shaka::DataNode>(result);


	Args result_vector = {result_value};

	return result_vector;

}


// (floor/ n1 n2)
Args floor_div_numbers(Args args, EnvPtr env) {

	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());
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

	NodePtr v1 = std::make_shared<shaka::DataNode>(q);
	NodePtr v2 = std::make_shared<shaka::DataNode>(r);
	
	Args result_vector = {v1, v2};

	return result_vector;

}


// (floor-quotient n1 n2)
Args floor_quotient_numbers(Args args, EnvPtr env) {
		

	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());
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

	NodePtr v1 = std::make_shared<shaka::DataNode>(q);
	
	Args result_vector = {v1};

	return result_vector;

}


// (floor-remainder n1 n2)
Args floor_remainder_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());
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

	NodePtr v1 = std::make_shared<shaka::DataNode>(r);
	
	Args result_vector = {v1};

	return result_vector;

}


// (truncate/ n1 n2)
Args truncate_div_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());

	shaka::Number r;
	shaka::Number q;


	r = n1 % n2;
	q = (n1 - r) / n2;

	NodePtr v1 = std::make_shared<shaka::DataNode>(q);
	NodePtr v2 = std::make_shared<shaka::DataNode>(r);
	
	Args result_vector = {v1, v2};

	return result_vector;


}

// (truncate-quotient n1 n2)
Args truncate_quotient_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());

	shaka::Number r = n1 % n2;
	shaka::Number q = (n1 - r) / n2;

	NodePtr v = std::make_shared<shaka::DataNode>(q);

	Args result_vector = {v};

	return result_vector;

}

// (truncate-remainder n1 n2)
Args truncate_remainder_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());

	shaka::Number r = n1 % n2;

	NodePtr v = std::make_shared<shaka::DataNode>(r);

	Args result_vector = {v};

	return result_vector;
}

// (quotient n1 n2)
Args quotient_numbers(Args args, EnvPtr env) {

	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());

	shaka::Number r = n1 % n2;
	shaka::Number q = (n1 - r) / n2;

	NodePtr v = std::make_shared<shaka::DataNode>(q);

	Args result_vector = {v};

	return result_vector;

}

// (remainder n1 n2)
Args remainder_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());

	shaka::Number r = n1 % n2;

	NodePtr v = std::make_shared<shaka::DataNode>(r);

	Args result_vector = {v};

	return result_vector;
}

// (modulo n1 n2)
Args modulo_numbers(Args args, EnvPtr env) {
	
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());
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

	NodePtr v1 = std::make_shared<shaka::DataNode>(r);
	
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

Args gcd_numbers(Args args, EnvPtr env) {

	shaka::Number result = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number next;
	for (std::size_t i = 1; i < args.size(); i++) {
		next = shaka::get<shaka::Number>(args[i]->get_data());
		result = gcd_pair(result, next); 
	}

	NodePtr result_value = std::make_shared<shaka::DataNode>(result);

	Args result_vector = {result_value};

	return result_vector;

}


// (lcm n1 ...)
Args lcm_numbers(Args args, EnvPtr env) {
	
	shaka::Number result = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number next;
	shaka::Number gcd;
	for (std::size_t i = 1; i < args.size(); i++) {
		next = shaka::get<shaka::Number>(args[i]->get_data());
		gcd = gcd_pair(result, next);
		result = (result*next)|gcd;
	}

	NodePtr result_value = std::make_shared<shaka::DataNode>(result);

	Args result_vector = {result_value};

	return result_vector;


}

// (numerator q)
Args numerator_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	
	shaka::Number result(boost::get<shaka::Rational>(n1.get_value()).get_numerator());

	NodePtr result_value = std::make_shared<shaka::DataNode>(result);
	
	Args result_vector = {result_value};

	return result_vector;


}

// (denominator q)
Args denominator_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());

	shaka::Number result(boost::get<shaka::Rational>(n1.get_value()).get_denominator());

	NodePtr result_value = std::make_shared<shaka::DataNode>(result);

	Args result_vector = {result_value};

	return result_vector;
}


// (floor x)
Args floor_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	if (n1.get_value().type() == typeid(shaka::Real)) {
		shaka::Number result(floor(boost::get<shaka::Real>(n1.get_value()).get_value()));
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else if (n1.get_value().type() == typeid(shaka::Integer)) {
		shaka::Number result(floor(boost::get<shaka::Integer>(n1.get_value()).get_value()));
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else {
		int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
		int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();

		shaka::Number result(floor((double) numerator / (double) denominator));
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
	}

}
// (ceiling x)
Args ceiling_numbers(Args args, EnvPtr env) {
  	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
  	if (n1.get_value().type() == typeid(shaka::Real)) {
    	shaka::Number result(ceil(boost::get<shaka::Real>(n1.get_value()).get_value()));
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
  	}
	else if (n1.get_value().type() == typeid(shaka::Integer)) {
		shaka::Number result(ceil(boost::get<shaka::Integer>(n1.get_value()).get_value()));
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else {
		int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
		int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();

		shaka::Number result(ceil((double) numerator / (double) denominator));
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
	}
}

// (truncate x)
Args truncate_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	if (n1.get_value().type() == typeid(shaka::Real)) {
		shaka::Number result(trunc(boost::get<shaka::Real>(n1.get_value()).get_value()));
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else if (n1.get_value().type() == typeid(shaka::Integer)) {
		shaka::Number result(trunc(boost::get<shaka::Integer>(n1.get_value()).get_value()));
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else {
		int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
		int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();

		shaka::Number result(trunc((double) numerator / (double) denominator));
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
	}
}

// (round x)
Args round_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());

	if (n1.get_value().type() == typeid(shaka::Real)) {
		shaka::Number result(round(boost::get<shaka::Real>(n1.get_value()).get_value()));
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else if (n1.get_value().type() == typeid(shaka::Integer)) {
		shaka::Number result(round(boost::get<shaka::Integer>(n1.get_value()).get_value()));
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else {
		int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
		int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();
		shaka::Number result(round((double) numerator / (double) denominator));
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
	}

}
/*
// (rationalize x y)
Args rationalize_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());

	if (n1.get_value().type() == typeid(shaka::Integer)) {
		Args n2_args = {args[1]};
		shaka::Number n2_trunc((abs_numbers(truncate_numbers(n2_args, env), env))[0]->get_data());
		shaka::Number result(n1 - n2);
		NodePtr result_value = std::make_shared<shaka::DataNode>(result);
		Args result_vector = {result_value};
		return result_vector;
	}

*/

// (exp z)
Args exp_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());

	if (n1.get_value().type() == typeid(shaka::Integer)) {
		shaka::Number result(exp(boost::get<shaka::Integer>(n1.get_value()).get_value()));
		shaka::Number truncated_result(
				trunc(
					boost::get<shaka::Real>(
						result.get_value()).get_value() * 100000000000) / 100000000000);
		NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else if (n1.get_value().type() == typeid(shaka::Real)) {
		shaka::Number result(exp(boost::get<shaka::Real>(n1.get_value()).get_value()));
		shaka::Number truncated_result(
				trunc(
					boost::get<shaka::Real>(
						result.get_value()).get_value() * 100000000000) / 100000000000);
		NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else {
		int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
		int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();
		shaka::Number result(exp((double) numerator / (double) denominator));	
		shaka::Number truncated_result(
				trunc(
					boost::get<shaka::Real>(
						result.get_value()).get_value() * 100000000000) / 100000000000);
		NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
		Args result_vector = {result_value};
		return result_vector;
	}

}

// (log z)

Args log_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());

	if (n1.get_value().type() == typeid(shaka::Integer)) {
		shaka::Number result(log(boost::get<shaka::Integer>(n1.get_value()).get_value()));
		shaka::Number truncated_result(
				trunc(
					boost::get<shaka::Real>(
						result.get_value()).get_value() * 100000000000) / 100000000000);
		NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else if (n1.get_value().type() == typeid(shaka::Real)) {
		shaka::Number result(log(boost::get<shaka::Real>(n1.get_value()).get_value()));
		shaka::Number truncated_result(
				trunc(
					boost::get<shaka::Real>(
						result.get_value()).get_value() * 100000000000) / 100000000000);
		NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else {
		int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
		int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();
		shaka::Number result(log((double) numerator / (double) denominator));	
		shaka::Number truncated_result(
				trunc(
					boost::get<shaka::Real>(
						result.get_value()).get_value() * 100000000000) / 100000000000);
		NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
		Args result_vector = {result_value};
		return result_vector;
	}

}


// (log z1 z2)
/*
Args log_n_numbers(Args args, EnvPtr env) {
	shaka::Number n1 = shaka::get<shaka::Number>(args[0]->get_data());
	shaka::Number n2 = shaka::get<shaka::Number>(args[1]->get_data());


	if (n1.get_value().type() == typeid(shaka::Integer)) {
		if (n2.get_value().type() == typeid(shaka::Integer)) {
		
			shaka::Number result(log(boost::get<shaka::Integer>(n1.get_value()).get_value())/
					log(boost::get<shaka::Integer>(n2.get_value()).get_value()));
			shaka::Number truncated_result(
					trunc(
						boost::get<shaka::Real>(
							result.get_value()).get_value() * 100000000000) / 100000000000);
			NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
			Args result_vector = {result_value};
			return result_vector;
			
		
		}
		shaka::Number result(log(boost::get<shaka::Integer>(n1.get_value()).get_value()));
		shaka::Number truncated_result(
				trunc(
					boost::get<shaka::Real>(
						result.get_value()).get_value() * 100000000000) / 100000000000);
		NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else if (n1.get_value().type() == typeid(shaka::Real)) {
		shaka::Number result(log(boost::get<shaka::Real>(n1.get_value()).get_value()));
		shaka::Number truncated_result(
				trunc(
					boost::get<shaka::Real>(
						result.get_value()).get_value() * 100000000000) / 100000000000);
		NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
		Args result_vector = {result_value};
		return result_vector;
	}
	else {
		int numerator = boost::get<shaka::Rational>(n1.get_value()).get_numerator();
		int denominator = boost::get<shaka::Rational>(n1.get_value()).get_denominator();
		shaka::Number result(log((double) numerator / (double) denominator));	
		shaka::Number truncated_result(
				trunc(
					boost::get<shaka::Real>(
						result.get_value()).get_value() * 100000000000) / 100000000000);
		NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
		Args result_vector = {result_value};
		return result_vector;
	}

	shaka::Number truncated_result(
			trunc(
				boost::get<shaka::Real>(
					result.get_value()).get_value() * 100000000000) / 100000000000);

	NodePtr result_value = std::make_shared<shaka::DataNode>(truncated_result);
	Args result_vector = {result_value};
	return result_vector;
}
*/
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
//Function neg = impl::neg_numbers;
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
Function floor = impl::floor_numbers;
Function ceiling = impl::ceiling_numbers;
Function truncate = impl::truncate_numbers;
Function round = impl::round_numbers;
Function exp = impl::exp_numbers;
Function log = impl::log_numbers;
} // namespace stdproc
} // namespace shaka

#endif // SHAKA_STDPROC_NUMBERS_ARITHMETIC_IMPL_H
